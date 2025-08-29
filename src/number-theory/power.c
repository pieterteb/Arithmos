#include <stdbool.h>

#include "arithmos/number-theory/power.h"



extern unsigned long long arithmos_power(unsigned long long base, unsigned long long exponent) {
    unsigned long long result = 1;

    while (1) {
        if (exponent & 1) result *= base;

        exponent >>= 1;
        if (exponent == 0) break;

        base *= base;
    }

    return result;
}

extern bool arithmos_power_safe(unsigned long long base, unsigned long long exponent, unsigned long long* result) {
    *result = 1;

    bool overflow = false;
    while (1) {
        if (exponent & 1) overflow |= __builtin_mul_overflow(base, *result, result);

        exponent >>= 1;
        if (exponent == 0) break;

        overflow |= __builtin_mul_overflow(base, base, &base);
    }

    return overflow;
}

extern unsigned long long arithmos_power_mod(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
    if (modulus == 0) return 0;

    unsigned long long result = 1 % modulus;

    while (1) {
        if (exponent & 1) result = (__uint128_t)base * result % modulus;

        exponent >>= 1;
        if (exponent == 0) break;

        base = (__uint128_t)base * base % modulus;
    }

    return result;
}
