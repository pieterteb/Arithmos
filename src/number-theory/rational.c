#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "arithmos/number-theory/rational.h"
#include "arithmos/number-theory/gcd.h"
#include "arithmos/number-theory/power.h"



typedef struct Arithmos_Rational128 {
    __uint128_t     numerator;
    __uint128_t     denominator;
    bool            sign;
} Arithmos_Rational128;

static void arithmos_rational128_from_uint128(Arithmos_Rational128* rational128, __uint128_t numerator, __uint128_t denominator, bool sign);
static void arithmos_rational128_simplify(Arithmos_Rational128* rational);


extern void arithmos_rational_init(Arithmos_Rational* rational) {
    *rational = ARITHMOS_RATIONAL_POSITIVE_ZERO;
}

extern void arithmos_rational_from_ull(Arithmos_Rational* rational, unsigned long long numerator, unsigned long long denominator, bool sign) {
    *rational = (Arithmos_Rational){ numerator, denominator, sign };
    arithmos_rational_simplify(rational);
}

extern void arithmos_rational_copy(Arithmos_Rational* destination, const Arithmos_Rational* source) {
    *destination = *source;
}

static void arithmos_rational128_from_uint128(Arithmos_Rational128* rational128, __uint128_t numerator, __uint128_t denominator, bool sign) {
    *rational128 = (Arithmos_Rational128){ numerator, denominator, sign };
    arithmos_rational128_simplify(rational128);
}

extern void arithmos_rational_print(FILE* stream, const Arithmos_Rational* rational) {
    if (rational->sign) fputc('-', stream);

    if (arithmos_rational_is_nan(rational)) {
        fprintf(stream, "NaN");
    } else if (arithmos_rational_is_infinity(rational)) {
        fprintf(stream, "Inf");
    } else if (rational->denominator != 1) {
        fprintf(stream, "%llu / %llu", rational->numerator, rational->denominator);
    } else {
        fprintf(stream, "%llu", rational->numerator);
    }
}


extern bool arithmos_rational_is_zero(const Arithmos_Rational* rational) {
    return rational->numerator == 0 && rational->denominator != 0;
}

extern bool arithmos_rational_is_infinity(const Arithmos_Rational* rational) {
    return rational->numerator != 0 && rational->denominator == 0;
}

extern bool arithmos_rational_is_nan(const Arithmos_Rational* rational) {
    return rational->numerator == 0 && rational->denominator == 0;
}

extern void arithmos_rational_simplify(Arithmos_Rational* rational) {
    unsigned long long gcd = arithmos_gcdull_fast(rational->numerator, rational->denominator);

    if (gcd == 0) return;

    rational->numerator /= gcd;
    rational->denominator /= gcd;
}

static void arithmos_rational128_simplify(Arithmos_Rational128* rational) {
    __uint128_t gcd = arithmos_gcdu128(rational->numerator, rational->denominator);

    if (gcd == 0) return;

    rational->numerator /= gcd;
    rational->denominator /= gcd;
}

extern int arithmos_rational_compare(Arithmos_Rational rational1, Arithmos_Rational rational2) {
    arithmos_rational_simplify(&rational1);
    arithmos_rational_simplify(&rational2);

    if (arithmos_rational_is_zero(&rational1) && arithmos_rational_is_zero(&rational2)) return 0;

    if (rational1.sign != rational2.sign) return rational2.sign - rational1.sign;

    unsigned long long gcd = arithmos_gcdull_fast(rational1.denominator, rational2.denominator);

    if (gcd == 0) return 0;

    __uint128_t numerator1 = (__uint128_t)rational1.numerator * (rational2.denominator / gcd);
    __uint128_t numerator2 = (__uint128_t)rational2.numerator * (rational1.denominator / gcd);

    return rational1.sign == false ? (numerator1 > numerator2) - (numerator1 < numerator2) : (numerator1 < numerator2) - (numerator1 > numerator2);
}

extern bool arithmos_rational_equals(Arithmos_Rational rational1, Arithmos_Rational rational2) {
    arithmos_rational_simplify(&rational1);
    arithmos_rational_simplify(&rational2);

    if (arithmos_rational_is_nan(&rational1) || arithmos_rational_is_nan(&rational2)) return false;

    return rational1.sign == rational2.sign && rational1.numerator == rational2.numerator && rational1.denominator == rational2.denominator;
}


extern void arithmos_rational_abs(Arithmos_Rational* rational) {
    rational->sign = false;
}

extern void arithmos_rational_negate(Arithmos_Rational* rational) {
    rational->sign = !rational->sign;
}

extern bool arithmos_rational_sum(Arithmos_Rational addend1, Arithmos_Rational addend2, Arithmos_Rational* result) {
    /* Take the difference of addend1 and addend2 if their signs differ. */
    if (addend1.sign != addend2.sign) {
        addend2.sign = !addend2.sign;

        return arithmos_rational_difference(addend1, addend2, result);
    }

    /* Deal with NaNs. */
    if (arithmos_rational_is_nan(&addend1) || arithmos_rational_is_nan(&addend2)) {
        *result = ARITHMOS_RATIONAL_POSITIVE_NAN;

        return false;
    }

    /* Deal with double infinities. */
    if (arithmos_rational_is_infinity(&addend1) && arithmos_rational_is_infinity(&addend2)) {
        *result = addend1;
        
        return false;
    }

    /*
    We use the relation a / b + c / d = (ad + bc) / bd. Since ad + bc can overflow, even as __uint128_t, we need to check for that. 
    Notice that, if ad + bc overflows in 128 bit representation, (ad + bc) / bd overflows in 64 bit representation as well. In the best case, we have
    bd == 2^64 - 1 and ad + bc == 2^128. Then (ad + bc) / bd > 2^64 - 1 which implies 64 bit integer overflow.
    */

    __uint128_t ad = (__uint128_t)addend1.numerator * addend2.denominator;
    __uint128_t bc = (__uint128_t)addend2.numerator * addend1.denominator;
    __uint128_t bd = (__uint128_t)addend1.denominator * addend2.denominator;

    __uint128_t numerator;
    bool overflow = __builtin_add_overflow(ad, bc, &numerator);

    Arithmos_Rational128 rational128;
    arithmos_rational128_from_uint128(
        &rational128,
        numerator,
        bd,
        false
    );

    arithmos_rational_from_ull(
        result,
        (unsigned long long)rational128.numerator,
        (unsigned long long)rational128.denominator,
        addend1.sign
    );

    return overflow || rational128.numerator > ULLONG_MAX || rational128.denominator > ULLONG_MAX;
}

extern bool arithmos_rational_difference(Arithmos_Rational minuend, Arithmos_Rational subtrahend, Arithmos_Rational* result) {
    /* Take the sum of minuend and subtrahend if their signs differ. */
    if (minuend.sign != subtrahend.sign) {
        subtrahend.sign = !subtrahend.sign;

        return arithmos_rational_sum(minuend, subtrahend, result);
    }

    /* Deal with NaNs. */
    if (arithmos_rational_is_nan(&minuend) || arithmos_rational_is_nan(&subtrahend)) {
        *result = ARITHMOS_RATIONAL_POSITIVE_NAN;

        return false;
    }

    /* Deal with double infinities. */
    if (arithmos_rational_is_infinity(&minuend) && arithmos_rational_is_infinity(&subtrahend)) {
        *result = ARITHMOS_RATIONAL_POSITIVE_NAN;

        return false;
    }

    /*
    We use the relation a / b - c / d = (ad - bc) / bd. Since ad - bc can not overflow as __uint128_t, we only have to check whether bc > ad and flip the sign in that case.
    */

    __uint128_t ad = (__uint128_t)minuend.numerator * subtrahend.denominator;
    __uint128_t bc = (__uint128_t)subtrahend.numerator * minuend.denominator;
    __uint128_t bd = (__uint128_t)minuend.denominator * subtrahend.denominator;

    bool flip_sign = ad < bc;
    __uint128_t numerator = flip_sign ? bc - ad : ad - bc;

    Arithmos_Rational128 rational128;
    arithmos_rational128_from_uint128(
        &rational128,
        numerator,
        bd,
        false
    );

    arithmos_rational_from_ull(
        result,
        (unsigned long long)rational128.numerator,
        (unsigned long long)rational128.denominator,
        flip_sign ? !minuend.sign : minuend.sign
    );

    if (arithmos_rational_is_zero(result)) result->sign = false;

    return rational128.numerator > ULLONG_MAX || rational128.denominator > ULLONG_MAX;
}

extern void arithmos_rational_invert(Arithmos_Rational* rational) {
    if (arithmos_rational_is_nan(rational)) {
        rational->sign = false;

        return;
    }

    unsigned long long temp = rational->numerator;
    rational->numerator = rational->denominator;
    rational->denominator = temp;

    arithmos_rational_simplify(rational);
}

extern bool arithmos_rational_product(Arithmos_Rational multiplier, Arithmos_Rational multiplicand, Arithmos_Rational* result) {
    Arithmos_Rational128 rational128;
    arithmos_rational128_from_uint128(
        &rational128,
        (__uint128_t)multiplier.numerator * multiplicand.numerator,
        (__uint128_t)multiplier.denominator * multiplicand.denominator,
        multiplier.sign ^ multiplicand.sign
    );

    arithmos_rational_from_ull(
        result,
        (unsigned long long)rational128.numerator,
        (unsigned long long)rational128.denominator,
        rational128.sign
    );

    if (arithmos_rational_is_zero(result)) result->sign = false;

    return rational128.numerator > ULLONG_MAX || rational128.denominator > ULLONG_MAX;
}

extern bool arithmos_rational_quotient(Arithmos_Rational dividend, Arithmos_Rational devisor, Arithmos_Rational* result) {
    arithmos_rational_invert(&devisor);

    return arithmos_rational_product(dividend, devisor, result);
}

extern bool arithmos_rational_power(Arithmos_Rational* base, unsigned long long exponent) {
    if (arithmos_rational_is_nan(base) || (arithmos_rational_is_infinity(base) && exponent == 0)) {
        *base = ARITHMOS_RATIONAL_POSITIVE_NAN;

        return false;
    }

    arithmos_rational_simplify(base);

    bool overflow = arithmos_power_safe(base->numerator, exponent, &base->numerator);
    overflow |= arithmos_power_safe(base->denominator, exponent, &base->denominator);

    if (base->sign && (exponent & 1) == 0) base->sign = false; 

    return overflow;
}


extern float arithmos_rational_to_f(const Arithmos_Rational* rational) {
    return rational->sign ? -(float)rational->numerator / (float)rational->denominator : (float)rational->numerator / (float)rational->denominator;
}

extern double arithmos_rational_to_d(const Arithmos_Rational* rational) {
    return rational->sign ? -(double)rational->numerator / (double)rational->denominator : (double)rational->numerator / (double)rational->denominator;
}

extern long double arithmos_rational_to_ld(const Arithmos_Rational* rational) {
    return rational->sign ? -(long double)rational->numerator / (long double)rational->denominator : (long double)rational->numerator / (long double)rational->denominator;
}
