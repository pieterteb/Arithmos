#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arithmos/number-theory/big_int.h"



static void arithmos_bigint_ensure_capacity(Arithmos_BigInt* bigint, size_t new_size);

static void arithmos_bigint_add_u64(Arithmos_BigInt* bigint, uint64_t addend);
static void arithmos_bigint_multiply_u64(Arithmos_BigInt* bigint, uint64_t factor);
static uint64_t arithmos_bigint_divide_u64(Arithmos_BigInt* bigint, uint64_t divisor);

static void arithmos_bigint_shallow_copy(Arithmos_BigInt* destination, const Arithmos_BigInt* source);
static int arithmos_bigint_compare_abs(const Arithmos_BigInt* bigint1, const Arithmos_BigInt* bigint2);


extern void arithmos_bigint_init(Arithmos_BigInt* bigint) {
    *bigint = (Arithmos_BigInt){
        NULL,
        0,
        0,
        false
    };
}

extern void arithmos_bigint_destroy(Arithmos_BigInt* bigint) {
    free(bigint->digits);
    arithmos_bigint_init(bigint);
}

extern size_t arithmos_bigint_shrink(Arithmos_BigInt* bigint) {
    bigint->size = bigint->digit_count;
    bigint->digits = realloc(bigint->digits, bigint->size * sizeof(uint64_t));

    return bigint->size * sizeof(uint64_t);
}

extern void arithmos_bigint_from_u64(Arithmos_BigInt* bigint, uint64_t value, bool sign) {
    arithmos_bigint_ensure_capacity(bigint, 1);

    bigint->digits[0] = value;
    bigint->digit_count = 1;
    bigint->sign = sign;
}

extern void arithmos_bigint_copy(Arithmos_BigInt* destination, const Arithmos_BigInt* source) {
    destination->digit_count = source->digit_count;
    destination->sign = source->sign;

    arithmos_bigint_ensure_capacity(destination, destination->digit_count);
    
    memcpy(destination->digits, source->digits, destination->digit_count * sizeof(uint64_t));
}

#define CHUNK_BASE      1000000000000000000ULL
#define CHUNK_DIGITS    18

extern void arithmos_bigint_from_string(Arithmos_BigInt* bigint, const char* string) {
    arithmos_bigint_from_u64(bigint, 0, false);

    // Handle sign.
    if (*string == '-') {
        bigint->sign = true;
        ++string;
    } else if (*string == '+') {
        ++string;
    }

    // Skip leading zeros.
    while (*string == '0') ++string;

    size_t length = strlen(string);
    if (length == 0) return;
    
    size_t start_count = length % CHUNK_DIGITS;
    char chunk_string[CHUNK_DIGITS + 1];

    // First (partial) chunk.
    if (start_count > 0) {
        strncpy(chunk_string, string, start_count);
        chunk_string[start_count] = '\0';

        uint64_t chunk = strtoull(chunk_string, NULL, 10);
        arithmos_bigint_add_u64(bigint, chunk);

        string += start_count;
    }

    // Full CHUNK_DIGITS-digit chunks.
    while (*string != 0) {
        strncpy(chunk_string, string, CHUNK_DIGITS);
        chunk_string[CHUNK_DIGITS] = '\0';

        uint64_t chunk = strtoull(chunk_string, NULL, 10);
        arithmos_bigint_multiply_u64(bigint, CHUNK_BASE);
        arithmos_bigint_add_u64(bigint, chunk);

        string += CHUNK_DIGITS;
    }
}

extern char* arithmos_bigint_to_string(const Arithmos_BigInt* bigint) {
    if (arithmos_bigint_is_zero(bigint)) return strdup("0");

    Arithmos_BigInt temp;
    arithmos_bigint_init(&temp);
    arithmos_bigint_copy(&temp, bigint);

    // Estimate max chunks needed.
    size_t max_chunks = (temp.digit_count * 64 + 59) / 60; // Each decimal chunk holds about 60 bits (log2(10 ^ 18) ~ 59.8).
    uint64_t* chunks = malloc(max_chunks * sizeof(uint64_t));
    size_t chunk_count = 0;

    while (!(temp.digit_count == 1 && temp.digits[0] == 0)) {
        uint64_t remainder = arithmos_bigint_divide_u64(&temp, CHUNK_BASE);
        chunks[chunk_count] = remainder;
        ++chunk_count;
    }

    // Convert chunks to string.
    size_t buffer_size = chunk_count * CHUNK_DIGITS + 2; // +1 for sign, +1 for \0.
    char* buffer = malloc(buffer_size);
    char* ptr = buffer;

    if (bigint->sign) {
        *ptr = '-';
        ++ptr;
    }

    // Print the highest chunk without leading zeros.
    ptr += sprintf(ptr, "%" PRIu64, chunks[chunk_count - 1]);

    // Remaining chunks, padded with leading zeros.
    for (__ssize_t i = chunk_count - 2; i >= 0; --i) {
        ptr += sprintf(ptr, "%018" PRIu64, chunks[i]);
    }

    *ptr = '\0';
    free(chunks);
    arithmos_bigint_destroy(&temp);

    return buffer;
}

#undef CHUNK_BASE
#undef CHUNK_DIGITS

static void arithmos_bigint_ensure_capacity(Arithmos_BigInt* bigint, size_t new_size) {
    if (new_size > bigint->size) {
        bigint->size = new_size * 2;
        bigint->digits = realloc(bigint->digits, bigint->size * sizeof(uint64_t));
    }
}

static void arithmos_bigint_add_u64(Arithmos_BigInt* bigint, uint64_t addend) {
    __uint128_t next_digit = (__uint128_t)bigint->digits[0] + addend;
    bigint->digits[0] = (uint64_t)next_digit;
    __uint128_t carry = next_digit >> 64;

    size_t i = 1;
    while (carry != 0 && i < bigint->digit_count) {
        next_digit = (__uint128_t)bigint->digits[i] + carry;
        bigint->digits[i] = (uint64_t)next_digit;

        carry = next_digit >> 64;
        ++i;
    }

    if (carry != 0) {
        arithmos_bigint_ensure_capacity(bigint, bigint->digit_count + 1);
        bigint->digits[bigint->digit_count] = (uint64_t)carry;
        ++bigint->digit_count;
    }
}

static void arithmos_bigint_multiply_u64(Arithmos_BigInt* bigint, uint64_t factor) {
    __uint128_t carry = 0;
    for (size_t i = 0; i < bigint->digit_count; ++i) {
        __uint128_t product = (__uint128_t)bigint->digits[i] * factor + carry;
        bigint->digits[i] = (uint64_t)product;
        
        carry = product >> 64;
    }

    if (carry != 0) {
        arithmos_bigint_ensure_capacity(bigint, bigint->digit_count + 1);
        bigint->digits[bigint->digit_count] = (uint64_t)carry;
        ++bigint->digit_count;
    }
}

static uint64_t arithmos_bigint_divide_u64(Arithmos_BigInt* bigint, uint64_t divisor) {
    if (divisor == 0) return 0;

    __uint128_t remainder = 0;

    for (__ssize_t i = bigint->digit_count - 1; i >= 0; --i) {
        __uint128_t current = (remainder << 64) | bigint->digits[i];
        bigint->digits[i] = (uint64_t)(current / divisor);
        remainder = current % divisor;
    }

    while (bigint->digit_count > 1 && bigint->digits[bigint->digit_count - 1] == 0) {
        --bigint->digit_count;
    }

    return (uint64_t)remainder;
}


extern bool arithmos_bigint_is_zero(const Arithmos_BigInt* bigint) {
    return bigint->digit_count == 1 && bigint->digits[0] == 0;
}


extern int arithmos_bigint_compare(const Arithmos_BigInt* bigint1, const Arithmos_BigInt* bigint2) {
    if (arithmos_bigint_is_zero(bigint1) && arithmos_bigint_is_zero(bigint2)) return 0;

    if (bigint1->sign != bigint2->sign) return bigint1->sign ? -1 : 1;

    if (bigint1->digit_count > bigint2->digit_count) return bigint1->sign ? -1 : 1;
    if (bigint1->digit_count < bigint2->digit_count) return bigint1->sign ? 1 : -1;

    for (__ssize_t i = bigint1->digit_count - 1; i >= 0; --i) {
        if (bigint1->digits[i] > bigint2->digits[i]) return bigint1->sign ? -1 : 1;
        if (bigint1->digits[i] < bigint2->digits[i]) return bigint1->sign ? 1 : -1;
    }

    return 0;
}

extern bool arithmos_bigint_equals(const Arithmos_BigInt* bigint1, const Arithmos_BigInt* bigint2) {
    return arithmos_bigint_compare(bigint1, bigint2) == 0;
}

extern void arithmos_bigint_abs(Arithmos_BigInt* bigint) {
    bigint->sign = false;
}

extern void arithmos_bigint_negate(Arithmos_BigInt* bigint) {
    bigint->sign = !bigint->sign;
}

static void arithmos_bigint_shallow_copy(Arithmos_BigInt* destination, const Arithmos_BigInt* source) {
    *destination = *source;
}

extern void arithmos_bigint_sum(const Arithmos_BigInt* addend1, const Arithmos_BigInt* addend2, Arithmos_BigInt* result) {
    if (addend1->sign != addend2->sign) {
        Arithmos_BigInt addend2_copy;
        arithmos_bigint_init(&addend2_copy);
        arithmos_bigint_shallow_copy(&addend2_copy, addend2);
        addend2_copy.sign = !addend2_copy.sign;

        arithmos_bigint_difference(addend1, &addend2_copy, result);

        return;
    }

    /* Copy the addends in case addend1 or addend2 overlaps with result. */
    Arithmos_BigInt addend1_copy;
    Arithmos_BigInt addend2_copy;
    arithmos_bigint_init(&addend1_copy);
    arithmos_bigint_init(&addend2_copy);
    arithmos_bigint_copy(&addend1_copy, addend1);
    arithmos_bigint_copy(&addend2_copy, addend2);

    size_t max_digits = addend1_copy.digit_count > addend2_copy.digit_count ? addend1_copy.digit_count : addend2_copy.digit_count;

    arithmos_bigint_ensure_capacity(result, max_digits + 1); // +1 for carry.
    result->digit_count = max_digits;
    result->sign = addend1_copy.sign;

    __uint128_t carry = 0;
    for (size_t i = 0; i < max_digits; ++i) {
        __uint128_t next_digit = carry;
        if (i < addend1_copy.digit_count) next_digit += addend1_copy.digits[i];
        if (i < addend2_copy.digit_count) next_digit += addend2_copy.digits[i];

        result->digits[i] = (uint64_t)next_digit;
        carry = next_digit >> 64;
    }

    if (carry != 0) {
        result->digits[result->digit_count] = (uint64_t)carry;
        ++result->digit_count;
    }

    if (arithmos_bigint_is_zero(result)) result->sign = false;

    arithmos_bigint_destroy(&addend1_copy);
    arithmos_bigint_destroy(&addend2_copy);
}

extern void arithmos_bigint_add(Arithmos_BigInt* result, const Arithmos_BigInt* addend) {
    if (result->sign != addend->sign) {
        Arithmos_BigInt addend_copy;
        arithmos_bigint_init(&addend_copy);
        arithmos_bigint_shallow_copy(&addend_copy, addend);
        addend_copy.sign = !addend_copy.sign;
        
        arithmos_bigint_subtract(result, &addend_copy);

        return;
    }

    Arithmos_BigInt addend_copy;
    arithmos_bigint_init(&addend_copy);
    arithmos_bigint_copy(&addend_copy, addend);

    size_t max_digits = result->digit_count > addend_copy.digit_count ? result->digit_count : addend_copy.digit_count;

    arithmos_bigint_ensure_capacity(result, max_digits + 1); // + 1 for carry.

    __uint128_t carry = 0;
    for (size_t i = 0; i < max_digits; ++i) {
        __uint128_t next_digit = carry;
        if (i < result->digit_count) next_digit += result->digits[i];
        if (i < addend_copy.digit_count) {
            next_digit += addend_copy.digits[i];
        } else if (carry == 0) {
            break;
        }

        result->digits[i] = (uint64_t)next_digit;
        carry = next_digit >> 64;
    }

    if (carry != 0) {
        result->digits[max_digits] = (uint64_t)carry;
        result->digit_count = max_digits + 1;
    } else {
        result->digit_count = max_digits;
    }

    if (arithmos_bigint_is_zero(result)) result->sign = false;

    arithmos_bigint_destroy(&addend_copy);
}

static int arithmos_bigint_compare_abs(const Arithmos_BigInt* bigint1, const Arithmos_BigInt* bigint2) {
    if (bigint1->digit_count < bigint2->digit_count) return -1;
    if (bigint1->digit_count > bigint2->digit_count) return 1;

    for (__ssize_t i = bigint1->digit_count - 1; i >= 0; --i) {
        if (bigint1->digits[i] < bigint2->digits[i]) return -1;
        if (bigint1->digits[i] > bigint2->digits[i]) return 1;
    }

    return 0;
}

extern void arithmos_bigint_difference(const Arithmos_BigInt* minuend, const Arithmos_BigInt* subtrahend, Arithmos_BigInt* result) {
    if (minuend->sign != subtrahend->sign) {
        Arithmos_BigInt subtrahend_copy;
        arithmos_bigint_init(&subtrahend_copy);
        arithmos_bigint_shallow_copy(&subtrahend_copy, subtrahend);
        subtrahend_copy.sign = !subtrahend_copy.sign;

        arithmos_bigint_sum(minuend, &subtrahend_copy, result);

        return;
    }

    int compare = arithmos_bigint_compare_abs(minuend, subtrahend);
    if (compare >= 0) {
        result->sign = minuend->sign;
    } else {
        result->sign = !minuend->sign;

        const Arithmos_BigInt* temp = minuend;
        minuend = subtrahend;
        subtrahend = temp;
    }

    Arithmos_BigInt minuend_copy;
    Arithmos_BigInt subtrahend_copy;
    arithmos_bigint_init(&minuend_copy);
    arithmos_bigint_init(&subtrahend_copy);
    arithmos_bigint_copy(&minuend_copy, minuend);
    arithmos_bigint_copy(&subtrahend_copy, subtrahend);

    arithmos_bigint_ensure_capacity(result, minuend_copy.digit_count);
    result->digit_count = minuend_copy.digit_count;
    
    __uint128_t borrow = 0;
    for (size_t i = 0; i < minuend_copy.digit_count; ++i) {
        __uint128_t left = minuend_copy.digits[i];
        __uint128_t right = borrow;
        if (i < subtrahend_copy.digit_count) right += subtrahend_copy.digits[i];

        if (left < right) {
            result->digits[i] = (uint64_t)(((__uint128_t)1 << 64) + left - right);
            borrow = 1;
        } else {
            result->digits[i] = (uint64_t)(left - right);
            borrow = 0;
        }
    }

    while (result->digit_count > 1 && result->digits[result->digit_count - 1] == 0) --result->digit_count;

    if (arithmos_bigint_is_zero(result)) result->sign = false;

    arithmos_bigint_destroy(&minuend_copy);
    arithmos_bigint_destroy(&subtrahend_copy);
}

extern void arithmos_bigint_subtract(Arithmos_BigInt* result, const Arithmos_BigInt* subtrahend) {
    if (result->sign != subtrahend->sign) {
        Arithmos_BigInt subtrahend_copy;
        arithmos_bigint_init(&subtrahend_copy);
        arithmos_bigint_shallow_copy(&subtrahend_copy, subtrahend);
        subtrahend_copy.sign = !subtrahend_copy.sign;

        arithmos_bigint_add(result, &subtrahend_copy);

        return;
    }

    Arithmos_BigInt subtrahend_copy;
    arithmos_bigint_init(&subtrahend_copy);
    arithmos_bigint_copy(&subtrahend_copy, subtrahend);
    subtrahend = &subtrahend_copy;

    const Arithmos_BigInt* minuend = result;
    int compare = arithmos_bigint_compare_abs(minuend, subtrahend);
    if (compare < 0) {
        result->sign = !result->sign;

        const Arithmos_BigInt* temp = minuend;
        minuend = subtrahend;
        subtrahend = temp;
    }

    arithmos_bigint_ensure_capacity(result, minuend->digit_count);
    result->digit_count = minuend->digit_count;
    
    __uint128_t borrow = 0;
    for (size_t i = 0; i < minuend->digit_count; ++i) {
        __uint128_t left = minuend->digits[i];
        __uint128_t right = borrow;
        if (i < subtrahend->digit_count) right += subtrahend->digits[i];

        if (left < right) {
            result->digits[i] = (uint64_t)(((__uint128_t)1 << 64) + left - right);
            borrow = 1;
        } else {
            result->digits[i] = (uint64_t)(left - right);
            borrow = 0;
        }
    }

    while (result->digit_count > 1 && result->digits[result->digit_count - 1] == 0) --result->digit_count;

    if (arithmos_bigint_is_zero(result)) result->sign = false;

    arithmos_bigint_destroy(&subtrahend_copy);
}

static void arithmos_bigint_karatsuba(const Arithmos_BigInt* multiplier, const Arithmos_BigInt* multiplicand, Arithmos_BigInt* result) {

}

extern void arithmos_bigint_product(const Arithmos_BigInt* multiplier, const Arithmos_BigInt* multiplicand, Arithmos_BigInt* result) {
    Arithmos_BigInt multiplier_copy;
    Arithmos_BigInt multiplicand_copy;
    arithmos_bigint_init(&multiplier_copy);
    arithmos_bigint_init(&multiplicand_copy);
    arithmos_bigint_copy(&multiplier_copy, multiplier);
    arithmos_bigint_copy(&multiplicand_copy, multiplicand);

    arithmos_bigint_ensure_capacity(result, multiplier_copy.digit_count + multiplicand_copy.digit_count);
    result->sign = multiplier->sign ^ multiplicand->sign;

    arithmos_bigint_karatsuba(&multiplier_copy, &multiplicand_copy, result);
}
