#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arithmos/number-theory/big_int.h"

int main() {
    Arithmos_BigInt b;

    arithmos_bigint_init(&b);
    assert(b.digit_count == 0);
    assert(b.size == 0);
    assert(b.digits == NULL);
    assert(b.sign == false);

    arithmos_bigint_from_u64(&b, 0, false);
    assert(b.digit_count == 1);
    assert(b.digits[0] == 0);
    assert(b.sign == false);
    arithmos_bigint_from_u64(&b, 1234567890ULL, false);
    assert(b.digit_count == 1);
    assert(b.digits[0] == 1234567890ULL);
    assert(b.sign == false);
    arithmos_bigint_from_u64(&b, 42ULL, true);
    assert(b.digit_count == 1);
    assert(b.digits[0] == 42ULL);
    assert(b.sign == true);

    Arithmos_BigInt a;
    arithmos_bigint_init(&a);

    arithmos_bigint_from_u64(&a, 9876543210ULL, true);
    arithmos_bigint_copy(&b, &a);
    assert(b.digit_count == a.digit_count);
    assert(b.sign == a.sign);
    assert(memcmp(b.digits, a.digits, b.digit_count * sizeof(uint64_t)) == 0);

    char* s;
    
    arithmos_bigint_from_string(&b, "0");
    s = arithmos_bigint_to_string(&b);
    assert(strcmp(s, "0") == 0);
    free(s);
    arithmos_bigint_from_string(&b, "-0");
    s = arithmos_bigint_to_string(&b);
    assert(strcmp(s, "0") == 0);
    free(s);
    arithmos_bigint_from_string(&b, "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    s = arithmos_bigint_to_string(&b);
    assert(strcmp(s, "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890") == 0);
    free(s);
    arithmos_bigint_from_string(&b, "-98765432109876543210");
    s = arithmos_bigint_to_string(&b);
    assert(strcmp(s, "-98765432109876543210") == 0);
    free(s);

    arithmos_bigint_from_u64(&b, 13, false);
    arithmos_bigint_shrink(&b);
    assert(b.size == 1);

    bool result;

    result = arithmos_bigint_is_zero(&b);
    assert(result == false);
    arithmos_bigint_from_u64(&b, 0, false);
    result = arithmos_bigint_is_zero(&b);
    assert(result == true);
    arithmos_bigint_from_u64(&b, 0, true);
    result = arithmos_bigint_is_zero(&b);
    assert(result == true);

    arithmos_bigint_from_u64(&a, 0, false);
    arithmos_bigint_from_u64(&b, 0, false);
    assert(arithmos_bigint_compare(&a, &b) == 0);
    arithmos_bigint_from_u64(&a, 0, true);
    assert(arithmos_bigint_compare(&a, &b) == 0);
    arithmos_bigint_from_u64(&a, 1, true);
    arithmos_bigint_from_u64(&b, 1, false);
    assert(arithmos_bigint_compare(&a, &b) == -1);
    assert(arithmos_bigint_compare(&b, &a) == 1);
    arithmos_bigint_from_string(&a, "12345678901234567890");
    arithmos_bigint_from_string(&b, "12345678901234567890");
    assert(arithmos_bigint_compare(&a, &b) == 0);
    arithmos_bigint_from_string(&b, "12345678901234567891");
    assert(arithmos_bigint_compare(&a, &b) == -1);
    assert(arithmos_bigint_compare(&b, &a) == 1);
    arithmos_bigint_from_string(&a, "-12345678901234567891");
    arithmos_bigint_from_string(&b, "-12345678901234567890");
    assert(arithmos_bigint_compare(&a, &b) == -1);
    arithmos_bigint_from_u64(&a, UINT64_MAX, false);
    arithmos_bigint_from_string(&b, "18446744073709551616");  // 2^64
    assert(arithmos_bigint_compare(&a, &b) == -1);
    arithmos_bigint_from_string(&a, "-99999999999999999999999999999");
    arithmos_bigint_from_string(&b, "1");
    assert(arithmos_bigint_compare(&a, &b) == -1);

    arithmos_bigint_from_u64(&a, 0, false);
    arithmos_bigint_from_u64(&b, 0, false);
    assert(arithmos_bigint_equals(&a, &b));
    arithmos_bigint_from_u64(&a, 0, true);
    assert(arithmos_bigint_equals(&a, &b));
    arithmos_bigint_from_string(&a, "12345678901234567890");
    arithmos_bigint_from_string(&b, "12345678901234567890");
    assert(arithmos_bigint_equals(&a, &b));
    arithmos_bigint_from_string(&a, "-99999999999999999999999999999");
    arithmos_bigint_from_string(&b, "1");
    assert(!arithmos_bigint_equals(&a, &b));

    arithmos_bigint_from_u64(&b, 55, false);
    arithmos_bigint_abs(&b);
    assert(b.sign == false);
    arithmos_bigint_from_u64(&b, 77, true);
    arithmos_bigint_abs(&b);
    assert(b.sign == false);
    arithmos_bigint_from_u64(&b, 0, false);
    arithmos_bigint_abs(&b);
    assert(arithmos_bigint_is_zero(&b));

    arithmos_bigint_from_u64(&a, 123, false);
    arithmos_bigint_negate(&a);
    assert(a.sign == true);
    arithmos_bigint_negate(&a);
    assert(a.sign == false);
    arithmos_bigint_from_u64(&a, 0, false);
    arithmos_bigint_negate(&a);
    assert(arithmos_bigint_is_zero(&a));
    arithmos_bigint_from_u64(&a, 999, false);
    arithmos_bigint_negate(&a);
    arithmos_bigint_negate(&a);
    assert(a.sign == false);

    Arithmos_BigInt result2;
    arithmos_bigint_init(&result2);

    arithmos_bigint_from_u64(&a, 1, false);
    arithmos_bigint_from_u64(&b, 2, false);
    arithmos_bigint_sum(&a, &b, &result2);
    s = arithmos_bigint_to_string(&result2);
    assert(strcmp(s, "3") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, 5, true);
    arithmos_bigint_from_u64(&b, 10, false);
    arithmos_bigint_sum(&a, &b, &result2);
    s = arithmos_bigint_to_string(&result2);
    assert(strcmp(s, "5") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, 3, true);
    arithmos_bigint_from_u64(&b, 3, false);
    arithmos_bigint_sum(&a, &b, &result2);
    s = arithmos_bigint_to_string(&result2);
    assert(strcmp(s, "0") == 0);
    free(s);
    arithmos_bigint_from_string(&a, "18446744073709551615");
    arithmos_bigint_from_u64(&b, 1, false);
    arithmos_bigint_sum(&a, &b, &result2);
    s = arithmos_bigint_to_string(&result2);
    assert(strcmp(s, "18446744073709551616") == 0);
    free(s);

    arithmos_bigint_from_u64(&a, 1, false);
    arithmos_bigint_from_u64(&b, 3, false);
    arithmos_bigint_add(&a, &b);
    s = arithmos_bigint_to_string(&a);
    assert(strcmp(s, "4") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, 1, false);
    arithmos_bigint_from_u64(&b, 3, true);
    arithmos_bigint_add(&a, &b);
    s = arithmos_bigint_to_string(&a);
    assert(strcmp(s, "-2") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, 1, true);
    arithmos_bigint_from_u64(&b, 3, false);
    arithmos_bigint_add(&a, &b);
    s = arithmos_bigint_to_string(&a);
    assert(strcmp(s, "2") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, 1, false);
    arithmos_bigint_from_u64(&b, 1, true);
    arithmos_bigint_add(&a, &b);
    s = arithmos_bigint_to_string(&a);
    assert(strcmp(s, "0") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, UINT64_MAX, false);
    arithmos_bigint_from_u64(&b, 1, false);
    arithmos_bigint_add(&a, &b);
    s = arithmos_bigint_to_string(&a);
    assert(strcmp(s, "18446744073709551616") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, 10, true);
    arithmos_bigint_add(&a, &a);
    s = arithmos_bigint_to_string(&a);
    assert(strcmp(s, "-20") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, UINT64_MAX, false);
    arithmos_bigint_add(&a, &a);
    s = arithmos_bigint_to_string(&a);
    assert(strcmp(s, "36893488147419103230") == 0);
    free(s);

    arithmos_bigint_from_u64(&a, 7, false);
    arithmos_bigint_from_u64(&b, 2, false);
    arithmos_bigint_difference(&a, &b, &result2);
    s = arithmos_bigint_to_string(&result2);
    assert(strcmp(s, "5") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, 2, false);
    arithmos_bigint_from_u64(&b, 7, false);
    arithmos_bigint_difference(&a, &b, &result2);
    s = arithmos_bigint_to_string(&result2);
    assert(strcmp(s, "-5") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, 3, true);
    arithmos_bigint_from_u64(&b, 3, false);
    arithmos_bigint_difference(&a, &b, &result2);
    s = arithmos_bigint_to_string(&result2);
    assert(strcmp(s, "-6") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, 0, false);
    arithmos_bigint_from_u64(&b, 0, false);
    arithmos_bigint_difference(&a, &b, &result2);
    s = arithmos_bigint_to_string(&result2);
    assert(strcmp(s, "0") == 0);
    free(s);
    arithmos_bigint_from_string(&a, "18446744073709551616");
    arithmos_bigint_from_u64(&b, 1, false);
    arithmos_bigint_difference(&a, &b, &result2);
    s = arithmos_bigint_to_string(&result2);
    assert(strcmp(s, "18446744073709551615") == 0);
    free(s);

    arithmos_bigint_from_u64(&a, 1, false);
    arithmos_bigint_from_u64(&b, 3, false);
    arithmos_bigint_subtract(&a, &b);
    s = arithmos_bigint_to_string(&a);
    assert(strcmp(s, "-2") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, 1, false);
    arithmos_bigint_from_u64(&b, 3, true);
    arithmos_bigint_subtract(&a, &b);
    s = arithmos_bigint_to_string(&a);
    assert(strcmp(s, "4") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, 1, true);
    arithmos_bigint_from_u64(&b, 3, false);
    arithmos_bigint_subtract(&a, &b);
    s = arithmos_bigint_to_string(&a);
    assert(strcmp(s, "-4") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, 1, false);
    arithmos_bigint_from_u64(&b, 1, false);
    arithmos_bigint_subtract(&a, &b);
    s = arithmos_bigint_to_string(&a);
    assert(strcmp(s, "0") == 0);
    free(s);
    arithmos_bigint_from_string(&a, "18446744073709551616");
    arithmos_bigint_from_u64(&b, 1, false);
    arithmos_bigint_subtract(&a, &b);
    s = arithmos_bigint_to_string(&a);
    assert(strcmp(s, "18446744073709551615") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, 10, true);
    arithmos_bigint_subtract(&a, &a);
    s = arithmos_bigint_to_string(&a);
    assert(strcmp(s, "0") == 0);
    free(s);
    arithmos_bigint_from_u64(&a, UINT64_MAX, false);
    arithmos_bigint_subtract(&a, &a);
    s = arithmos_bigint_to_string(&a);
    assert(strcmp(s, "0") == 0);
    free(s);


    arithmos_bigint_destroy(&a);
    arithmos_bigint_destroy(&b);
    arithmos_bigint_destroy(&result2);

    return 0;
}
