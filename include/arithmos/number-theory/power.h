#ifndef POWER_H
#define POWER_H


#include <stdbool.h>



/**
 * @brief Computes the power of a base and exponent.
 * 
 * This function does not check for integer overflow.
 * 
 * @param base The base.
 * @param exponent The exponent.
 * 
 * @return `base` to the power of `exponent`.
 * 
 * Example:
 * ```c
 * unsigned long long result = arithmos_power(3, 3); // result == 27
 * ```
 * 
 * @note `arithmos_power(0, 0) == 1` be definition.
 */
extern unsigned long long arithmos_power(unsigned long long base, unsigned long long exponent);

/**
 * @brief Computes the power of a base and exponent and detects integer overflow.
 * 
 * @param base The base.
 * @param exponent The exponent.
 * @param result Pointer to `unsigned long long` which stores `base` to the power of `exponent`.
 * 
 * @return `true` if integer overflow occurs, `false` otherwise.
 * 
 * Example:
 * ```c
 * unsigned long long result;
 * bool overflow = arithmos_power_safe(2, 64, &result);
 * // overflow == true
 * // result == 0
 * ```
 * 
 * @note `arithmos_power_safe(0, 0, &result)` will set result to `0` by definition.
 */
extern bool arithmos_power_safe(unsigned long long base, unsigned long long exponent, unsigned long long* result);

/**
 * @brief Computes the power modular power of a base and exponent.
 * 
 * @param base The base.
 * @param exponent The exponent.
 * @param modulus The modulus.
 * 
 * @return `base` to the power of `exponent` modulo `modulus`. If `modulus == 0`, `0` is returned.
 * 
 * Example:
 * ```c
 * unsigned long long result = arithmos_power_mod(3, 3, 5); // result == 2
 * ```
 * 
 * @note `arithmos_power_mod(0, 0, modulus) == 0` if `modulus != 0` by definition.
 */
extern unsigned long long arithmos_power_mod(unsigned long long base, unsigned long long exponent, unsigned long long modulus);



#endif /* POW_H */
