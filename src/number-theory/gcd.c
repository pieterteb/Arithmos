#include <limits.h>

#include "arithmos/number-theory/gcd.h"
#include "arithmos/number-theory/int128.h"


extern long long arithmos_gcdll(long long a, long long b) {
    unsigned long long ua = a < 0 ? (a == LLONG_MIN ? 1ULL << 63 : (unsigned long long)-a) : a;
    unsigned long long ub = b < 0 ? (b == LLONG_MIN ? 1ULL << 63 : (unsigned long long)-b) : b;

    while (ub) {
        unsigned long long temp = ub;
        ub = ua % ub;
        ua = temp;
    }

    return (long long)ua;
}

extern unsigned long long arithmos_gcdull(unsigned long long a, unsigned long long b) {
    /*
    The GCD is computed using the Euclidean algorithm. One can verify that

        gcd(a, b) = a,                  if b = 0    (1)
        gcd(a, b) = gcd(b, a mod b),    otherwise.  (2)

    By repeatedly applying (2), we eventually reach a situation like (1), where we can return a.
    */

    while (b) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}


extern __int128_t arithmos_gcd128(__int128_t a, __int128_t b) {
    __uint128_t ua = a < 0 ? (a == INT128_MAX ? (__uint128_t)1 << 127 : (__uint128_t)-a) : a;
    __uint128_t ub = b < 0 ? (b == INT128_MAX ? (__uint128_t)1 << 127 : (__uint128_t)-b) : b;

    while (ub) {
        __uint128_t temp = ub;
        ub = ua % ub;
        ua = temp;
    }

    return (__int128_t)ua;
}

extern __uint128_t arithmos_gcdu128(__uint128_t a, __uint128_t b) {
    while (b) {
        __uint128_t temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}


extern long long arithmos_gcdll_fast(long long a, long long b) {
    unsigned long long ua = a < 0 ? (a == LLONG_MIN ? 1ULL << 63 : (unsigned long long)-a) : a;
    unsigned long long ub = b < 0 ? (b == LLONG_MIN ? 1ULL << 63 : (unsigned long long)-b) : b;

    if (ua == 0) return (long long)ub;
    if (ub == 0) return (long long)ua;

    const int i = __builtin_ctzll(ua);
    ua >>= i;
    const int j = __builtin_ctzll(ub);
    ub >>= j;
    const int k = i < j ? i : j;

    while (1) {
        if (ua > ub) {
            unsigned long long temp = ua;
            ua = ub;
            ub = temp;
        }

        ub -= ua;

        if (ub == 0)
            return (long long)(ua << k);
        
        ub >>= __builtin_ctzll(ub);
    }
}

extern unsigned long long arithmos_gcdull_fast(unsigned long long a, unsigned long long b) {
    /*
    The GCD is computed usign the binary GCD algorithm. One can verify that

        gcd(a, b) = a,                  if b = 0                    (1)
        gcd(2a, 2b) = 2 * gcd(a, b);    so 2 is a common devisor    (2)
        gcd(a, 2b) = gcd(a, b),         if a is odd                 (3)
        gcd(a, b) = gcd(a, b - a),      if a, b odd and a <= b.     (4)

    We start by applying (2) for the greatest common power of 2. Now we know that at least
    one of a and b is odd. If we apply (3), both a and b are odd so (4) can be applied. Therefore, 
    by repeating (3) and (4), we eventually reach a situation like (1), where we can return.
    */

    if (a == 0) return b;
    if (b == 0) return a;

    // Relation (2) and (3)
    const int i = __builtin_ctzll(a);
    a >>= i;
    const int j = __builtin_ctzll(b);
    b >>= j;
    const int k = i < j ? i : j;

    while (1) {
        // Relation (4)
        if (a > b) {
            unsigned long long temp = a;
            a = b;
            b = temp;
        }
        b -= a;

        // Relation (1)
        if (b == 0) return a << k;
        
        // Relation (3)
        b >>= __builtin_ctzll(b);
    }
}


// #include <stdbool.h>

// void* arithmos_general_gcd(const void* a, const void* b, void (*copy_func)(void**, const void*), void (*destroy_func)(void*), bool (*is_zero_func)(const void*), void (*modulo_func)(const void*, const void*, void**)) {
//     void* a_copy;
//     copy_func(&a_copy, a);
//     void* b_copy;
//     copy_func(&b_copy, b);

//     void* temp;
//     while (!is_zero_func(b_copy)) {
//         copy_func(&temp, b_copy);
//         modulo_func(a_copy, b_copy, &b_copy);
//         copy_func(&a_copy, temp);
//     }

//     destroy_func(b_copy);
//     destroy_func(temp);

//     return a_copy;
// }
