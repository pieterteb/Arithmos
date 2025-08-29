#ifndef GCD_H
#define GCD_H



/**
 * @brief Computes the greatest common divisor (GCD) of two signed integers.
 * 
 * This function implements a simple version of the Euclidean GCD algorithm, which uses the relation `gcd(a, b) == gcd(b, a % b)`. Without major compiler optimization, this function generally outperforms `arithmos_gcdll_fast`.
 * 
 * @param a The first integer.
 * @param b The second integer.
 * 
 * @return The greatest common divisor of `a` and `b`.
 * 
 * Example:
 * ```c
 * long long result = arithmos_gcdll(48, -18); // result == 6
 * ```
 * 
 * @note `arithmos_gcdll(0, 0) == 0` by definition.
 */
extern long long arithmos_gcdll(long long a, long long b);

/**
 * @brief Computes the greatest common divisor (GCD) of two unsigned integers.
 * 
 * This function implements a simple version of the Euclidean GCD algorithm. Without major compiler optimization, this function generally outperforms `arithmos_gcdull_fast`.
 * 
 * @param a The first unsigned integer.
 * @param b The second unsigned integer.
 * 
 * @return The greatest common divisor of `a` and `b`.
 * 
 * Example:
 * ```c
 * unsigned long long result = arithmos_gcdull(48, 18); // result == 6
 * ```
 * 
 * @note `arithmos_gcdull(0, 0) == 0` by definition.
 */
extern unsigned long long arithmos_gcdull(unsigned long long a, unsigned long long b);


/**
 * @brief Computes the greatest common divisor (GCD) of two signed integers.
 * 
 * This function implements a simple version of the Euclidean GCD algorithm. It supports 128 bit signed integer types.
 * 
 * @param a The first integer.
 * @param b The second integer.
 * 
 * @return The greatest common divisor of `a` and `b`.
 * 
 * Example:
 * ```c
 * __int128_t result = arithmos_gcd128(48, 18); // result == 6
 * ```
 * 
 * @note `arithmos_gcd128(0, 0) == 0` by definition.
 */
extern __int128_t arithmos_gcd128(__int128_t a, __int128_t b);

/**
 * @brief Computes the greatest common divisor (GCD) of two unsigned integers.
 * 
 * This function implements a simple version of the Euclidean GCD algorithm. It supports 128 bit unsigned integer types.
 * 
 * @param a The first unsigned integer.
 * @param b The second unsigned integer.
 * 
 * @return The greatest common divisor of `a` and `b`.
 * 
 * Example:
 * ```c
 * __int128_t result = arithmos_gcdu128(48, 18); // result == 6
 * ```
 * 
 * @note `arithmos_gcdu128(0, 0) == 0` by definition.
 */
extern __uint128_t arithmos_gcdu128(__uint128_t a, __uint128_t b);


/**
 * @brief Computes the greatest common divisor (GCD) of two signed integers.
 * 
 * This function implements an optimized version of the binary GCD (Stein's) algorithm, which avoids the modulus operation by using bitwise operations. With compiler optimization, this function is usually faster than `arithmos_gcdll`.
 * 
 * @param a The first integer.
 * @param b The second integer.
 * 
 * @return The greatest common divisor of `a` and `b`.
 * 
 * Example:
 * ```c
 * long long result = arithmos_gcdll_fast(48, -18); // result == 6
 * ```
 * 
 * @note `arithmos_gcdll_fast(0, 0) == 0` by definition.
 */
extern long long arithmos_gcdll_fast(long long a, long long b);

/**
 * @brief Computes the greatest common divisor (GCD) of two unsigned integers.
 * 
 * This function implements an optimized version of the binary GCD (Stein's) algorithm, which avoids the modulus operation by using bitwise operations. With compiler optimization, this function is usually faster than `arithmos_gcdull`.
 * 
 * @param a The first unsigned integer.
 * @param b The second unsigned integer.
 * 
 * @return The greatest common divisor of `a` and `b`.
 * 
 * Example:
 * ```c
 * unsigned long long result = arithmos_gcdull_fast(48, 18); // result = 6
 * ```
 * 
 * @note `arithmos_gcdull_fast(0, 0) == 0` by definition.
 */
extern unsigned long long arithmos_gcdull_fast(unsigned long long a, unsigned long long b);



#endif /* GCD_H */