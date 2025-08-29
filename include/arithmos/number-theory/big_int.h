#ifndef BIG_INT_H
#define BIG_INT_H


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>



/**
 * Struct for arbitrary-precision integers. The struct represents an integer in base `2 ^ (8 * sizeof(uint64_t))`, which equals to `2 ^ 64`. 
 * The array `digits` represents the number
 * 
 *      `digits[digit_count - 1] * (2 ^ 64) ^ (digit_count - 1) + ... + digits[1] * (2 ^ 64) ^ 1 + digits[0] * (2 ^ 64) ^ 0`.
 * 
 * The sign is positive if `sign == false` and negative if `sign == true`.
 */
typedef struct Arithmos_BigInt {
    uint64_t*   digits;
    size_t      digit_count;
    size_t      size;
    bool        sign;
} Arithmos_BigInt;


/**
 * @brief Initializes a big integer.
 * 
 * Initializing a big integer is required before assigning it a value. Initializing an already initialized big integer can result in memory leakage. After destroying a big integer, it is not required to re-initialize it.
 * 
 * @param bigint Big integer to initialize.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt bigint;
 * arithmos_bigint_init(&bigint); // bigint == 0
 * ```
 */
extern void arithmos_bigint_init(Arithmos_BigInt* bigint);

/**
 * @brief Frees all memory used by a big integer, and re-initialize said big integer.
 * 
 * Because of the implicit re-initialization, it is not requried to initialize `bigint` manually after destroying it.
 * 
 * @param bigint The big int to destroy.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt bigint;
 * arithmos_bigint_init(&bigint);
 * arithmos_bigint_destroy(&bigint); // bigint.digits has been freed and bigint == { NULL, 0, 0, false }
 * ```
 */
extern void arithmos_bigint_destroy(Arithmos_BigInt* bigint);

/**
 * @brief Shrinks allocated memory block used by big integer down to its minimum size such that it can hold its current value.
 * 
 * This function can be used to reclaim unused memory in case memory is sparse.
 * 
 * @param bigint The big integer to shrink.
 * 
 * @return The size of the allocated memory used by `bigint` in bytes.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt bigint;
 * arithmos_bigint_init(&bigint);
 * arithmos_bigint_from_string(&bigint, "12345678901234567890"); // bigint requires and uses 16 bytes of memory here.
 * arithmos_bigint_from_u64(&bigint, 5, false); // bigint now requires 8 bytes, but still uses 16 bytes.
 * arithmos_bigint_shrink(&bigint); // bigint now requires and uses 8 bytes.
 * ```
 */
extern size_t arithmos_bigint_shrink(Arithmos_BigInt* bigint);

/**
 * @brief Asigns a given 64-bit unsigned integer to a big integer.
 * 
 * @param bigint Big integer to assign.
 * @param value The value.
 * @param sign The sign.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt bigint;
 * arithmos_bigint_init(&bigint);
 * arithmos_bigint_from_u64(&bigint, 303, true); // bigint = -303
 * ```
 */
extern void arithmos_bigint_from_u64(Arithmos_BigInt* bigint, uint64_t value, bool sign);

/**
 * @brief Clones a big integer to another big integer.
 * 
 * This function creates a hard copy of `source`. That is, not the pointer to the digits array is copied, but the actual contents of the array.
 * 
 * @param destination The destination big int.
 * @param source The source big int.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt source;
 * arithmos_bigint_init(&source);
 * arithmos_bigint_from_string(&source, "1234567890"); // source = 1234567890
 * Arithmos_BigInt destination;
 * arithmos_bigint_init(&destination);
 * arithmos_bigint_copy(&destionation, &source); // destination = 1234567890
 * ```
 */
extern void arithmos_bigint_copy(Arithmos_BigInt* destination, const Arithmos_BigInt* source);

/**
 * @brief Creates a big integer from a string in base 10.
 * 
 * @param bigint The big integer.
 * @param string The string.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt bigint;
 * arithmos_bigint_init(&bigint);
 * arithmos_bigint_from_string(&bigint, "123456789012345678901234567890"); // bigint = 123456789012345678901234567890
 * ```
 */
extern void arithmos_bigint_from_string(Arithmos_BigInt* bigint, const char* string);

/**
 * @brief Converts a big integer to a string in base 10.
 * 
 * @param bigint The big integer to convert.
 * 
 * @return A null-terminated `char` pointer that contains the big integer in decimal form.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt bigint;
 * arithmos_bigint_init(&bigint);
 * arithmos_bigint_from_string(&bigint, "-123456789012345678901234567890");
 * char* string = arithmos_bigint_to_string(&bigint); // string == "-123456789012345678901234567890"
 * ```
 */
extern char* arithmos_bigint_to_string(const Arithmos_BigInt* bigint);


/**
 * @brief Checks whether a big integer has a value of zero.
 * 
 * @param bigint The big integer.
 * 
 * @return `true` if `bigint` has a value of `0`, `false` otherwise.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt bigint;
 * arithmos_bigint_init(&bigint);
 * arithmos_bigint_from_u64(&bigint, 0, false);
 * bool result = arithmos_bigint_is_zero(&bigint); // result == true
 * ```
 */
extern bool arithmos_bigint_is_zero(const Arithmos_BigInt* bigint);


/**
 * @brief Compares two big intgers.
 * 
 * @param bigint1 The first big integer.
 * @param bigint2 The second big integer.
 * 
 * @return `-1` if `bigint1 < bigint2`, `1` if `bigint1 > bigint2`, and `0` if `bigint1 == bigint2`.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt bigint1;
 * Arithmos_BigInt bigint2;
 * arithmos_bigint_init(&bigint1);
 * arithmos_bigint_init(&bigint2);
 * arithmos_bigint_from_u64(&bigint1, 33, true);
 * arithmos_bigint_from_u64(&bigint2, 1, false);
 * int result = arithmos_bigint_compare(&bigint1, &bigint2); // result == -1
 * ```
 */
extern int arithmos_bigint_compare(const Arithmos_BigInt* bigint1, const Arithmos_BigInt* bigint2);

/**
 * @brief Checks whether two big integers are equal.
 * 
 * @param bigint1 The first big integer.
 * @param bigint2 The second big integer.
 * 
 * @return `true` if `bigint1 == bigint2`, `false` otherwise.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt bigint1;
 * Arithmos_BigInt bigint2;
 * arithmos_bigint_init(&bigint1);
 * arithmos_bigint_init(&bigint2);
 * arithmos_bigint_from_u64(&bigint1, 13, false);
 * arithmos_bigint_from_u64(&bigint2, 13, false);
 * bool result = arithmos_bigint_equals(&bigint1, &bigint2); // result == true
 * ```
 */
extern bool arithmos_bigint_equals(const Arithmos_BigInt* bigint1, const Arithmos_BigInt* bigint2);

/**
 * @brief Makes a big integer positive.
 * 
 * @param bigint The big integer to make positive.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt* bigint;
 * arithmos_bigint_init(&bigint);
 * arithmos_bigint_from_u64(&bigint, 4, true); // bigint = -4
 * arithmos_bigint_abs(&bigint); // bigint = 4
 * ```
 */
extern void arithmos_bigint_abs(Arithmos_BigInt* bigint);

/**
 * @brief Negates a big integer.
 * 
 * @param bigint The big integer to negate.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt* bigint;
 * arithmos_bigint_init(&bigint);
 * arithmos_bigint_from_u64(&bigint, 37, false); // bigint = 37
 * arithmos_bigint_negate(&bigint); // bigint = -37
 * ```
 * 
 * @note `0` will be negated to `-0` which is purely an internal value. In practice, `-0` is always interpreted as `0`.
 */
extern void arithmos_bigint_negate(Arithmos_BigInt* bigint);

/**
 * @brief Computes the sum of two big integers.
 * 
 * @param addend1 The first big integer.
 * @param addend2 The second big integer.
 * @param result The big integer which stores the sum of `addend1` and `addend2`.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt bigint1;
 * Arithmos_BigInt bigint2;
 * Arithmos_BigInt result;
 * arithmos_bigint_init(&bigint1);
 * arithmos_bigint_init(&bigint2);
 * arithmos_bigint_init(&result);
 * arithmos_bigint_from_u64(&bigint1, 69, false);
 * arithmos_bigint_from_u64(&bigint2, 420, false);
 * arithmos_bigint_sum(&bigint1, &bigint2, &result); // result = 489
 * ```
 */
extern void arithmos_bigint_sum(const Arithmos_BigInt* addend1, const Arithmos_BigInt* addend2, Arithmos_BigInt* result);

/**
 * @brief Adds a big integer to another big integer.
 * 
 * @param result The big integer that is added to.
 * @param addend The big integer that is added to `result`.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt bigint1;
 * Arithmos_BigInt bigint2;
 * arithmos_bigint_init(&bigint1);
 * arithmos_bigint_init(&bigint2);
 * arithmos_bigint_from_u64(&bigint1, 5, false);
 * arithmos_bigint_from_u64(&bigint2, 6, false);
 * arithmos_bigint_add(&bigint1, &bigint2); // bigint1 = 11
 * ```
 */
extern void arithmos_bigint_add(Arithmos_BigInt* result, const Arithmos_BigInt* addend);

/**
 * @brief Computes the difference of two big integers.
 * 
 * @param minuend The minuend.
 * @param subtrahend The subtrahend.
 * @param result The big integer which stores the difference of `minuend` and `subtrahend`.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt bigint1;
 * Arithmos_BigInt bigint2;
 * Arithmos_BigInt result;
 * arithmos_bigint_init(&bigint1);
 * arithmos_bigint_init(&bigint2);
 * arithmos_bigint_init(&result);
 * arithmos_bigint_from_u64(&bigint1, 69, false);
 * arithmos_bigint_from_u64(&bigint2, 420, false);
 * arithmos_bigint_difference(&bigint1, &bigint2, &result); // result = -351
 * ```
 */
extern void arithmos_bigint_difference(const Arithmos_BigInt* minuend, const Arithmos_BigInt* subtrahend, Arithmos_BigInt* result);

/**
 * @brief Subtracts a big integer from another big integer.
 * 
 * @param result The big integer that is subtracted from.
 * @param subtrahend The big integer that is subtracted from `result`.
 * 
 * Example:
 * ```c
 * Arithmos_BigInt bigint1;
 * Arithmos_BigInt bigint2;
 * arithmos_bigint_init(&bigint1);
 * arithmos_bigint_init(&bigint2);
 * arithmos_bigint_from_u64(&bigint1, 69, false);
 * arithmos_bigint_from_u64(&bigint2, 420, false);
 * arithmos_bigint_add(&bigint1, &bigint2); // bigint1 = -351
 * ```
 */
extern void arithmos_bigint_subtract(Arithmos_BigInt* result, const Arithmos_BigInt* subtrahend);



#endif /* BIG_INT_H */
