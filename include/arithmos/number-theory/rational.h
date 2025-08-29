#ifndef RATIONAL_H
#define RATIONAL_H


#include <stdbool.h>
#include <stdio.h>



/* Some constants. */

#define ARITHMOS_RATIONAL_POSITIVE_ZERO     ((Arithmos_Rational){ 0, 1, false })
#define ARITHMOS_RATIONAL_NEGATIVE_ZERO     ((Arithmos_Rational){ 0, 1, true })
#define ARITHMOS_RATIONAL_POSITIVE_INFINITY ((Arithmos_Rational){ 1, 0, false })
#define ARITHMOS_RATIONAL_NEGATIVE_INFINITY ((Arithmos_Rational){ 1, 0, true })
#define ARITHMOS_RATIONAL_POSITIVE_NAN      ((Arithmos_Rational){ 0, 0, false })
#define ARITHMOS_RATIONAL_NEGATIVE_NAN      ((Arithmos_Rational){ 0, 0, true })



/**
 * Struct for rational numbers. The struct represents the fraction
 * 
 *      numerator / denominator,
 * 
 * positive if `sign == false` and negative if `sign == true`. A division by `0` is interpreted as infinity, either positive or negative. 
 * `+-0 / 0` is interpreted as +-NaN, corresponding to the macros `ARITHMOS_RATIONAL_POSITIVE_NAN` and `ARITHMOS_RATIONAL_NEGATIVE_NAN`.
 */
typedef struct Arithmos_Rational {
    unsigned long long  numerator;
    unsigned long long  denominator;
    bool                sign;
} Arithmos_Rational;


/**
 * @brief Initializes a rational to zero.
 * 
 * @param rational The rational to initialize.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational;
 * arithmos_rational_init(&rational); // rational == ARITHMOS_RATIONAL_POSITIVE_ZERO
 * ```
 */
extern void arithmos_rational_init(Arithmos_Rational* rational);

/**
 * @brief Initializes a rational to a given value and simplifies it.
 * 
 * @param rational The rational to initialize.
 * @param numerator The numerator.
 * @param denominator The denominator.
 * @param sign The sign.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational;
 * arithmos_rational_from_ull(&rational, 3, 6, false); // rational == { 1, 2, false }
 * ```
 */
extern void arithmos_rational_from_ull(Arithmos_Rational* rational, unsigned long long numerator, unsigned long long denominator, bool sign);

/**
 * @brief Copies a rational to another rational.
 * 
 * @param destination The destination rational.
 * @param source The source rational.
 * 
 * Example:
 * ```c
 * Arithmos_Rational destination;
 * Arithmos_Rational source = arithmos_rational_create(22, 7, false);
 * arithmos_rational_copy(&destination, &source); // destination == { 22, 7, false }
 * ```
 */
extern void arithmos_rational_copy(Arithmos_Rational* destination, const Arithmos_Rational* source);

/**
 * @brief Prints rational to output stream.
 * 
 * The print format for regular fractions is [- (if `sign == true`)] <numerator> / <denominator>. If `denominator == 1`, only the numerator is printed. For infinity and NaN, the sign is printed if negative followed by "Inf" or "NaN" respectively.
 * 
 * @param stream The stream to print to.
 * @param rational The rational.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational = arithmos_rational_create(7, 33, true);
 * arithmos_rational_print(stdout, &rational);
 * 
 * printf("\n");
 * 
 * rational = arithmos_rational_create(1, 0, false);
 * arithmos_rational_print(stdout, &rational);
 * 
 * // Output:
 * // -7 / 33
 * // Inf
 * ```
 */
extern void arithmos_rational_print(FILE* stream, const Arithmos_Rational* rational);


/**
 * @brief Checks whether a rational is a zero.
 * 
 * @param rational The rational to check.
 * 
 * @return `true` if `rational == ARITHMOS_RATIONAL_POSITIVE_ZERO` or `rational == ARITHMOS_RATIONAL_NEGATIVE_ZERO`, `false` otherwise.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational = ARITHMOS_RATIONAL_NEGATIVE_ZERO;
 * bool result = arithmos_rational_is_zero(&rational); // result == true
 * ```
 */
extern bool arithmos_rational_is_zero(const Arithmos_Rational* rational);

/**
 * @brief Checks whether a rational is an infinity.
 * 
 * @param rational The rational to check.
 * 
 * @return `true` if `rational == ARITHMOS_RATIONAL_POSITIVE_INFINITY` or `rational == ARITHMOS_RATIONAL_NEGATIVE_INFINITY`, `false` otherwise.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational = ARITHMOS_RATIONAL_POSITIVE_INFINITY;
 * bool result = arithmos_rational_is_infinity(&rational); // result == true
 * ```
 */
extern bool arithmos_rational_is_infinity(const Arithmos_Rational* rational);

/**
 * @brief Checks whether a rational is a NaN.
 * 
 * @param rational The rational to check.
 * 
 * @return `true` if `rational == ARITHMOS_RATIONAL_POSITIVE_NAN` or `rational == ARITHMOS_RATIONAL_NEGATIVE_NAN`, `false` otherwise.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational = ARITHMOS_RATIONAL_NEGATIVE_NAN;
 * bool result = arithmos_rational_is_nan(&rational); // result == true
 * ```
 */
extern bool arithmos_rational_is_nan(const Arithmos_Rational* rational);

/**
 * @brief Simplifies a rational number.
 * 
 * This function behaves like you expect for regular fractions. For fractions with numerator or denominator 0, the following applies.
 * 
 *      If `numerator == 0 && denominator != 0`, the denominator is set to `1`.
 * 
 *      If `numerator != 0 && denominator == 0`, the numerator is set to `1`. The rational can be interpreted as negative or positive infinity, depending on the sign.
 * 
 *      If `numerator == 0 && denominator == 0`, There is no canonical interpretation of this number, and will therefore be referred to as NaN or -Nan, depending on the sign.
 * 
 * @param rational Pointer to rational to be simplified.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational = { 33, 22, false };
 * arithmos_rational_simplify(&rational); // rational == { 3, 2, false }
 * 
 * rational = { 42, 0, true };
 * arithmos_rational_simplify(&rational); // rational == { 1, 0, true }
 * ```
 */
extern void arithmos_rational_simplify(Arithmos_Rational* rational);

/**
 * @brief Compares two rationals.
 * 
 * This function behaves like you would expect for regular fractions. For infinities, we have the following rules:
 * 
 *      -oo < r < oo for any rational r,
 * 
 *      -oo == -oo,
 * 
 *      oo == oo.
 * 
 * @param rational1 The first rational.
 * @param rational2 The second rational.
 * 
 * @return `-1` if `rational1 < rational2`, `1` if `rational1 > rational2` and `0` if `rational1 == rational2`.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational1 = arithmos_rational_create(22, 7, false);
 * Arithmos_Rational rational2 = arithmos_rational_create(333, 106, false);
 * int result = arithmos_rational_compare(rational1, rational2); // result == 1
 * ```
 * 
 * @note If `arithmos_rational_is_nan(&rational1)` or `arithmos_rational_is_nan(&rational2)`, the result is undefined.
 */
extern int arithmos_rational_compare(Arithmos_Rational rational1, Arithmos_Rational rational2);

/**
 * @brief Checks whether two rationals are equal.
 * 
 * @param rational1 The first rational.
 * @param rational2 The second rational.
 * 
 * @return `true` if `rational1 == rational2`, `false` otherwise.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational1 = arithmos_rational_create(3, 7, false);
 * Arithmos_Rational rational2 = arithmos_rational_create(6, 14, false);
 * bool result = arithmos_rational_equals(rational1, rational2); // result == true
 * ```
 * 
 * @note `ARITHMOS_RATIONAL_POSITIVE_NAN` and `ARITHMOS_RATIONAL_NEGATIVE_NAN` are always unequal to another rational, even to themselves.
 */
extern bool arithmos_rational_equals(Arithmos_Rational rational1, Arithmos_Rational rational2);


/**
 * @brief Makes a rational positive.
 * 
 * This function sets the sign of `rational` to `false`.
 * 
 * @param rational The rational to make positive.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational = arithmos_rational_create(16, 9, true);
 * arithmos_rational_abs(&rational); // rational == { 16, 9, false }
 * ```
 */
extern void arithmos_rational_abs(Arithmos_Rational* rational);

/**
 * @brief Negates a rational.
 * 
 * This function flips the sign of `rational`.
 * 
 * @param rational The rational to be negated.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational = arithmos_rational_create(5, 7, false);
 * arithmos_rational_negate(&rational); // rational == { 5, 7, true }
 * ```
 */
extern void arithmos_rational_negate(Arithmos_Rational* rational);

/**
 * @brief Computes the sum of two rationals and detects integer overflow.
 * 
 * This function behaves like you would expect for regular fractions. For infinities, we have the following rules:
 * 
 *      -oo + -oo = -oo,
 * 
 *      oo + oo = oo,
 * 
 *      -oo + oo = NaN,
 * 
 *      oo + r = oo for any rational r,
 * 
 *      -oo + r = -oo for any rational r.
 * 
 * @param addend1 The first rational.
 * @param addend2 The second rational.
 * @param result Pointer to `Arithmos_Rational` which stores the sum of `addend1` and `addend2`.
 * 
 * @return `true` if integer overflow occurs, `false` otherwise.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational1 = arithmos_rational_create(1, 3, false);
 * Arithmos_Rational rational2 = arithmos_rational_create(1, 6, false);
 * Arithmos_Rational result;
 * bool overflow = arithmos_rational_sum(rational1, rational2, &result);
 * // overflow == false
 * // result == { 1, 2, false }
 * ```
 * 
 * @note If `arithmos_rational_is_nan(&addend1)` or `arithmos_rational_is_nan(&addend2)`, the result will be `ARITHMOS_RATIONAL_POSITIVE_NAN`.
 */
extern bool arithmos_rational_sum(Arithmos_Rational addend1, Arithmos_Rational addend2, Arithmos_Rational* result);

/**
 * @brief Computes the difference of two rationals and detects integer overflow.
 * 
 * This function behaves like you would expect for regular fractions. For infinities, we have the following rules:
 * 
 *      -oo - oo = -oo,
 * 
 *      oo - -oo = oo,
 * 
 *      -oo - -oo = NaN,
 * 
 *      oo - r = oo for any rational r,
 * 
 *      r - oo = -oo for any rational r.
 * 
 * @param minuend The first rational.
 * @param subtrahend The second rational.
 * @param result Pointer to `Arithmos_Rational` which stores the difference of `minuend` and `subtrahend`.
 * 
 * @return `true` if integer overflow occurs, `false` otherwise.
 * 
 * Example:
 * ```
 * Arithmos_Rational rational1 = arithmos_rational_create(1, 2, false);
 * Arithmos_Rational rational2 = arithmos_rational_create(1, 3, false);
 * Arithmos_Rational result;
 * bool overflow = arithmos_rational_difference(rational1, rational2, &result);
 * // overflow == false
 * // result == { 1, 6, false }
 * ```
 * 
 * @note If `arithmos_rational_is_nan(&minuend)` or `arithmos_rational_is_nan(&subtrahend)`, the result will be `ARITHMOS_RATIONAL_POSITIVE_NAN`.
 */
extern bool arithmos_rational_difference(Arithmos_Rational minuend, Arithmos_Rational subtrahend, Arithmos_Rational* result);

/**
 * @brief Inverts a rational.
 * 
 * This function behaves like you would expect for regular fractions. For infinities, we have the following rules:
 * 
 *      1 / oo = 1 / -oo = 0,
 * 
 *      1 / 0 = oo,
 * 
 * @param rational The rational.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational = arithmos_rational_create(3, 14, false);
 * arithmos_rational_invert(&rational); // rational == { 14, 3, false }
 * ```
 * 
 * @note If `arithmos_rational_is_nan(rational)`, the result is `ARITHMOS_RATIONAL_POSITIVE_NAN`.
 */
extern void arithmos_rational_invert(Arithmos_Rational* rational);

/**
 * @brief Computes the product of two rationals and detects integer overflow.
 * 
 * This function behaves like you would expect for regular fractions. For infinities, we have the following rules:
 * 
 *      oo * oo = oo,
 * 
 *      oo * -oo = -oo,
 * 
 *      -oo * -oo = oo,
 * 
 *      0 * oo = 0 * -oo = -0 * oo = -0 * -oo = NaN,
 * 
 *      r * oo = sgn(r) * oo for any nonzero rational r,
 * 
 *      r * -oo = -sgn(r) * oo for any nonzero rational r.
 * 
 * @param multiplier The first rational.
 * @param multiplicand The second rational.
 * @param result Pointer to `Arithmos_Rational` which stores the product of `multiplier` and `multiplicand`.
 * 
 * @return `true` if integer overflow occurs, `false` otherwise.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational1 = arithmos_rational_create(2, 3, true);
 * Arithmos_Rational rational2 = arithmos_rational_create(3, 4, true);
 * Arithmos_Rational result;
 * arithmos_rational_product(rational1, rational2, &result); // result == { 1, 2, false }
 * ```
 * 
 * @note If `arithmos_rational_is_nan(&multiplier)` or `arithmos_rational_is_nan(&multiplicand)`, the result will be `ARITHMOS_RATIONAL_POSITIVE_NAN`.
 */
extern bool arithmos_rational_product(Arithmos_Rational multiplier, Arithmos_Rational multiplicand, Arithmos_Rational* result);

/**
 * @brief Computes the quotient of two rationals and detects integer overflow.
 * 
 * This function's behaviour is equivalent to taking the product of `devisor` inverted and `dividend`.
 * 
 * @param dividend The first rational.
 * @param devisor The second rational.
 * @param result Pointer to `Arithmos_Rational` which stores the quotient of `dividend` and `devisor`.
 * 
 * @return `true` if integer overflow occurs, `false` otherwise.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational1 = arithmos_rational_create(2, 3, true);
 * Arithmos_Rational rational2 = arithmos_rational_create(4, 3, true);
 * Arithmos_Rational result;
 * arithmos_rational_quotient(rational1, rational2, &result); // result == { 1, 2, false }
 * ```
 * 
 * @note If `arithmos_rational_is_nan(&dividend)` or `arithmos_rational_is_nan(&devisor)`, the result will be `ARITHMOS_RATIONAL_POSITIVE_NAN`.
 */
extern bool arithmos_rational_quotient(Arithmos_Rational dividend, Arithmos_Rational devisor, Arithmos_Rational* result);

/**
 * @brief Computes the power of a rational and exponent.
 * 
 * This function behaves like you would expect. There are some special cases:
 * 
 *      oo ^ 0 = -oo ^ 0 = NaN,
 * 
 *      NaN ^ e = NaN.
 * 
 * @param base The base.
 * @param exponent The exponent.
 * 
 * @return `base` to the power of exponent. If `arithmos_rational_is_zero(base)` and `exponent == 0`, `1` is returned by definition.
 */
extern bool arithmos_rational_power(Arithmos_Rational* base, unsigned long long exponent);


/**
 * @brief Converts rational to float.
 * 
 * @param rational The rational to convert.
 * 
 * @return `float` obtained from `rational`.
 * 
 * Example:
 * ```c
 * Aritihmos_Rational rational = arithmos_rational_create(3, 4, true);
 * float result = arithmos_rational_to_f(&rational); // result == -0.75f
 * ```
 */
extern float arithmos_rational_to_f(const Arithmos_Rational* rational);

/**
 * @brief Converts rational to double.
 * 
 * @param rational The rational to convert.
 * 
 * @return `double` obtained from `rational`.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational = arithmos_rational_create(3, 4, true);
 * double result = arithmos_rational_to_d(&rational); // result == -0.75
 * ```
 */
extern double arithmos_rational_to_d(const Arithmos_Rational* rational);

/**
 * @brief Converts rational to long double.
 * 
 * @param rational The rational to convert.
 * 
 * @return `long double` obtained from `rational`.
 * 
 * Example:
 * ```c
 * Arithmos_Rational rational = arithmos_rational_create(3, 4, true);
 * long double result = arithmos_rational_to_ld(&rational); // result == (long double)-0.75
 */
extern long double arithmos_rational_to_ld(const Arithmos_Rational* rational);



#endif /* RATIONAL_H */
