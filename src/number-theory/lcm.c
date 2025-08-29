#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#include "arithmos/number-theory/gcd.h"



extern long long arithmos_lcmll(long long a, long long b) {
    if (a == 0 || b == 0) return 0;

    unsigned long long ua = (unsigned long long)(a < 0 ? -a : a);
    unsigned long long ub = (unsigned long long)(b < 0 ? -b : b);

    return (long long)((ua / arithmos_gcdull(ua, ub)) * ub);
}

extern bool arithmos_lcmll_safe(long long a, long long b, long long* result) {
    assert(result != NULL);

    if (a == 0 || b == 0) {
        *result = 0;
        return false;
    }

    unsigned long long ua = a < 0 ? (a == LLONG_MIN ? 1ULL << 63 : (unsigned long long)-a) : a;
    unsigned long long ub = b < 0 ? (b == LLONG_MIN ? 1ULL << 63 : (unsigned long long)-b) : b;

    *result = (long long)(ua / arithmos_gcdull(ua, ub));

    return __builtin_mul_overflow((unsigned long long)*result, ub, result) || *result < 0;
}

extern unsigned long long arithmos_lcmull(unsigned long long a, unsigned long long b) {
    if (a == 0 || b == 0) return 0;

    return (a / arithmos_gcdull(a, b)) * b;
}

extern bool arithmos_lcmull_safe(unsigned long long a, unsigned long long b, unsigned long long* result) {
    assert(result != NULL);

    if (a == 0 || b == 0) {
        *result = 0;
        return false;
    }

    *result = a / arithmos_gcdull(a, b);

    return __builtin_mul_overflow(*result, b, result);
}

extern long long arithmos_lcmll_fast(long long a, long long b) {
    if (a == 0 || b == 0) return 0;

    unsigned long long ua = (unsigned long long)(a < 0 ? -a : a);
    unsigned long long ub = (unsigned long long)(b < 0 ? -b : b);

    return (long long)((ua / arithmos_gcdull_fast(ua, ub)) * ub);
}

extern bool arithmos_lcmll_fast_safe(long long a, long long b, long long* result) {
    assert(result != NULL);

    if (a == 0 || b == 0) {
        *result = 0;
        return false;
    }

    unsigned long long ua = a < 0 ? (a == LLONG_MIN ? 1ULL << 63 : (unsigned long long)-a) : a;
    unsigned long long ub = b < 0 ? (b == LLONG_MIN ? 1ULL << 63 : (unsigned long long)-b) : b;

    *result = (long long)(ua / arithmos_gcdull_fast(ua, ub));

    return __builtin_mul_overflow((unsigned long long)*result, ub, result) || *result < 0;
}

extern unsigned long long arithmos_lcmull_fast(unsigned long long a, unsigned long long b) {
    if (a == 0 || b == 0) return 0;

    return (a / arithmos_gcdull_fast(a, b)) * b;
}

extern bool arithmos_lcmull_fast_safe(unsigned long long a, unsigned long long b, unsigned long long* result) {
    assert(result != NULL);

    if (a == 0 || b == 0) {
        *result = 0;
        return false;
    }

    *result = a / arithmos_gcdull_fast(a, b);

    return __builtin_mul_overflow(*result, b, result);
}
