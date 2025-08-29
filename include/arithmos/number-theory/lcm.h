#ifndef LCM_H
#define LCM_H


#include <stdbool.h>



/**
 * @brief Computes the least common multiple (LCM) of two signed integers.
 * 
 * This function uses `arithmos_gcdll` to compute LCM. Without major compiler optimization, this function generally outperforms `arithmos_lcmll_fast`.
 * 
 * @param a The first integer.
 * @param b The second integer.
 * 
 * @return The least common multiple of `a` and `b`.
 * 
 * Example:
 * ```c
 * long long result = arithmos_lcmll(12, -15); // result == 60
 * ```
 * 
 * @note `arithmos_lcmll(0, 0) == 0` by definition.
 */
extern long long arithmos_lcmll(long long a, long long b);

/**
 * @brief Computes the least common multiple (LCM) of two signed integers and detects integer overflow.
 * 
 * This function uses `arithmos_gcdll` to compute LCM. Without major compiler optimization, this function generally outperforms `arithmos_lcmll_fast_safe`.
 * 
 * @param a The first integer.
 * @param b The second integer.
 * @param result Pointer to `long long` which stores the LCM of `a` and `b`.
 * 
 * @return `true` if integer overflow occured, `false` otherwise.
 * 
 * Example:
 * ```c
 * long long result;
 * bool overflow = arithmos_lcmll_safe(12, -15, &result); 
 * // overflow == false
 * // result == 60
 * ```
 * 
 * @note `arithmos_lcmll_safe(0, 0, &result)` yields `result == 0` by definition.
 */
extern bool arithmos_lcmll_safe(long long a, long long b, long long* result);

/**
 * @brief Computes the least common multiple (LCM) of two unsigned integers.
 * 
 * This function uses `arithmos_gcdull` to compute LCM. Without major compiler optimization, this function generally outperforms `arithmos_lcmull_fast`.
 * 
 * @param a The first unsigned integer.
 * @param b The second unsigned integer.
 * 
 * @return The least common multiple of `a` and `b`.
 * 
 * Example:
 * ```c
 * long long result = arithmos_lcmull(12, 15); // result == 60
 * ```
 * 
 * @note `arithmos_lcmull(0, 0) == 0` by definition.
 */
extern unsigned long long arithmos_lcmull(unsigned long long a, unsigned long long b);

/**
 * @brief Computes the least common multiple (LCM) of two unsigned integers and detects integer overflow.
 * 
 * This function uses `arithmos_gcdull` to compute LCM. Without major compiler optimization, this function generally outperforms `arithmos_lcmull_fast_safe`.
 * 
 * @param a The first unsigned integer.
 * @param b The second unsigned integer.
 * @param result Pointer to `unsigned long long` which stores the LCM of `a` and `b`.
 * 
 * @return `true` if integer overflow occured, `false` otherwise.
 * 
 * Example:
 * ```c
 * unsigned long long result;
 * bool overflow = arithmos_lcmull_safe(12, 15, &result); 
 * // overflow == false
 * // result == 60
 * ```
 * 
 * @note `arithmos_lcmull_safe(0, 0, &result)` yields `result == 0` by definition.
 */
extern bool arithmos_lcmull_safe(unsigned long long a, unsigned long long b, unsigned long long* result);

/**
 * @brief Computes the least common multiple (LCM) of two signed integers.
 * 
 * This function uses `arithmos_gcdll_fast` to compute LCM. With compiler optimization, this function is usually faster than `arithmos_lcmll`.
 * 
 * @param a The first integer.
 * @param b The second integer.
 * 
 * @return The least common multiple of `a` and `b`.
 * 
 * Example:
 * ```c
 * long long result = arithmos_lcmll_fast(12, -15); // result == 60
 * ```
 * 
 * @note `arithmos_lcmll_fast(0, 0) == 0` by definition.
 */
extern long long arithmos_lcmll_fast(long long a, long long b);

/**
 * @brief Computes the least common multiple (LCM) of two signed integers and detects integer overflow.
 * 
 * This function uses `arithmos_gcdll_fast` to compute LCM. With compiler optimization, this function is usually faster than `arithmos_lcmll_safe`.
 * 
 * @param a The first integer.
 * @param b The second integer.
 * @param result Pointer to `long long` which stores the LCM of `a` and `b`.
 * 
 * @return `true` if integer overflow occured, `false` otherwise.
 * 
 * Example:
 * ```c
 * long long result;
 * bool overflow = arithmos_lcmll_fast_safe(12, -15, &result); 
 * // overflow == false
 * // result == 60
 * ```
 * 
 * @note `arithmos_lcmll_fast_safe(0, 0, &result)` yields `result == 0` by definition.
 */
extern bool arithmos_lcmll_fast_safe(long long a, long long b, long long* result);

/**
 * @brief Computes the least common multiple (LCM) of two unsigned integers.
 * 
 * This function uses `arithmos_gcdull_fast` to compute LCM. With compiler optimization, this function is usually faster than `arithmos_lcmull`.
 * 
 * @param a The first unsigned integer.
 * @param b The second unsigned integer.
 * 
 * @return The least common multiple of `a` and `b`.
 * 
 * Example:
 * ```c
 * unsigned long long result = arithmos_lcmull_fast(12, 15); // result == 60
 * ```
 * 
 * @note `arithmos_lcmull_fast(0, 0) == 0` by definition.
 */
extern unsigned long long arithmos_lcmull_fast(unsigned long long a, unsigned long long b);

/**
 * @brief Computes the least common multiple (LCM) of two signed integers and detects integer overflow.
 * 
 * This function uses `arithmos_gcdull_fast` to compute LCM. With compiler optimization, this function is usually faster than `arithmos_lcmull_safe`.
 * 
 * @param a The first unsigned integer.
 * @param b The second unsigned integer.
 * @param result Pointer to `long long` which stores the LCM of `a` and `b`.
 * 
 * @return `true` if integer overflow occured, `false` otherwise.
 * 
 * Example:
 * ```c
 * unsigned long long result;
 * bool overflow = arithmos_lcmull_fast_safe(12, 15, &result); 
 * // overflow == false
 * // result == 60
 * ```
 * 
 * @note `arithmos_lcmull_fast_safe(0, 0, &result)` yields `result == 0` by definition.
 */
extern bool arithmos_lcmull_fast_safe(unsigned long long a, unsigned long long b, unsigned long long* result);



#endif /* LCM_H */
