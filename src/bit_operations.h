// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#ifndef ARITHMOS_BIT_OPERATIONS_H_
#define ARITHMOS_BIT_OPERATIONS_H_


#include <assert.h>

#include "cpu_features.h"
#include "inline.h"

#if ARITHMOS_CPU_HAS_BMI1
#    include <immintrin.h>
#endif  // ARITHMOS_CPU_HAS_BMI1

#include "arithmos/core/types.h"



#ifndef __has_builtin
#    error "__has_builtin macro is required."
#endif  // #ifndef __has_builtin



// Returns the index of the first set bit of `x`, starting at the least significant bit position. If `x` is `0`,
// the result is undefined.
static INLINE unsigned internal_bsf_u32(const arith_u32 x) {
#if ARITHMOS_CPU_HAS_BMI1

    return _tzcnt_u32(x);

#elif __has_builtin(__builtin_ctzll)

    static_assert(sizeof(unsigned long long) >= sizeof(arith_u64), "size mismatch");

    return (unsigned)__builtin_ctz(x);

#else

    // Implementation of De Bruijn bit scan.

    // clang-format off
    static const unsigned index32[32] = {
         0,  1, 28,  2, 29, 14, 24,  3,
        30, 22, 20, 15, 25, 17,  4,  8,
        31, 27, 13, 23, 21, 19, 16,  7,
        26, 12, 18,  6, 11,  5, 10,  9
    };
    // clang-format on

    return index32[((x & -x) * (arith_u32)0x077CB531) >> 27];

#endif  // #if ARITHMOS_CPU_HAS_BMI1
}

// Returns the index of the first set bit of `x`, starting at the least significant bit position. If `x` is `0`,
// the result is undefined.
static INLINE unsigned internal_bsf_u64(const arith_u64 x) {
#if ARITHMOS_CPU_HAS_BMI1

    return (unsigned)_tzcnt_u64(x);

#elif __has_builtin(__builtin_ctz)

    static_assert(sizeof(unsigned long long) >= sizeof(arith_u64), "size mismatch");

    return (unsigned)__builtin_ctzll(x);

#else

    // Implementation of De Bruijn bit scan.

    // clang-format off
    static const unsigned index64[64] = {
         0,  1, 48,  2, 57, 49, 28,  3,
        61, 58, 50, 42, 38, 29, 17,  4,
        62, 55, 59, 36, 53, 51, 43, 22,
        45, 39, 33, 30, 24, 18, 12,  5,
        63, 47, 56, 27, 60, 41, 37, 16,
        54, 35, 52, 21, 44, 32, 23, 11,
        46, 26, 40, 15, 34, 20, 31, 10,
        25, 14, 19,  9, 13,  8,  7,  6
    };
    // clang-format on

    return index64[((x & -x) * (arith_u64)0x03f79d71b4cb0a89) >> 58];

#endif  // #if ARITHMOS_CPU_HAS_BMI1
}


// Returns the number of trailing `0`-bits in `x`, starting at the least significant bit position. If `x` is `0`,
// the result is `32`.
static INLINE unsigned internal_ctz_u32(const arith_u32 x) {
#if ARITHMOS_CPU_HAS_BMI1

    return _tzcnt_u32(x);

#else

    if (x == 0)
        return 32;

    return internal_bsf_u32(x);

#endif  // #if ARITHMOS_CPU_HAS_BMI1
}

// Returns the number of trailing `0`-bits in `x`, starting at the least significant bit position. If `x` is `0`,
// the result is `64`.
static INLINE unsigned internal_ctz_u64(const arith_u64 x) {
#if ARITHMOS_CPU_HAS_BMI1

    return (unsigned)_tzcnt_u64(x);

#else

    if (x == 0)
        return 64;

    return internal_bsf_u64(x);

#endif  // #if ARITHMOS_CPU_HAS_BMI1
}



#endif  // #ifndef ARITHMOS_BIT_OPERATIONS_H_
