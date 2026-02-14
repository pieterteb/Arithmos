// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#ifndef ARITHMOS_NUMERIC_INTERNAL_H_
#define ARITHMOS_NUMERIC_INTERNAL_H_


#include "cpu_features.h"
#include "inline.h"

#if ARITHMOS_CPU_HAS_BMI2
#    include <immintrin.h>
#endif  // #if ARITHMOS_CPU_HAS_BMI2

#include "arithmos/core/types.h"



// Computes the absolute value of `x`. The behaviour is undefined if
// the result cannot be represented as a value of type `arith_i32`.
static INLINE arith_i32 internal_abs_i32(const arith_i32 x) {
    return (x < 0) ? -x : x;
}

// Computes the absolute value of `x`. The behaviour is undefined if
// the result cannot be represented as a value of type `arith_i64`.
static INLINE arith_i64 internal_abs_i64(const arith_i64 x) {
    return (x < 0) ? -x : x;
}

// Computes the absolute value of `x`, and returns it as an unsigned value.
static INLINE arith_u32 internal_unsigned_abs_i32(const arith_i32 x) {
    return (x < 0) ? -(arith_u32)x : (arith_u32)x;
}

// Computes the absolute value of `x`, and returns it as an unsigned value.
static INLINE arith_u64 internal_unsigned_abs_i64(const arith_i64 x) {
    return (x < 0) ? -(arith_u64)x : (arith_u64)x;
}


// Computes `multiplier * multiplicand`, and returns it as a `arith_u128`.
static INLINE arith_u128 internal_multiply_u64(const arith_u64 multiplier, const arith_u64 multiplicand) {
#if ARITHMOS_CPU_HAS_BMI2

    arith_u64 high_bits;
    const arith_u64 low_bits = _mulx_u64(multiplier, multiplicand, (unsigned long long*)&high_bits);

    return ((arith_u128)high_bits << 64) | low_bits;

#else

    return (arith_u128)multiplier * multiplicand;

#endif  // #if ARITHMOS_CPU_HAS_BMI2
}


// Computes `multiplier * multiplicand (mod modulus)`. If `modulus` is `0`, the behaviour is undefined.
// If `multiplier * multiplicand` is negative, the result will be negative following the natural
// behaviour of the `%` operator.
static INLINE arith_i32 internal_mod_mul_i32(const arith_i32 multiplier, const arith_i32 multiplicand,
                                             const arith_u32 modulus) {
    return (arith_i32)((arith_i64)multiplier * multiplicand % modulus);
}

// Computes `multiplier * multiplicand (mod modulus)`. If `modulus` is `0`, the behaviour is undefined.
// If `multiplier * multiplicand` is negative, the result will be negative following the natural
// behaviour of the `%` operator.
static INLINE arith_i64 internal_mod_mul_i64(const arith_i64 multiplier, const arith_i64 multiplicand,
                                             const arith_u64 modulus) {
    return (arith_i64)((arith_i128)multiplier * multiplicand % modulus);
}

// Computes `(multiplier * multiplicand) % modulus`. If `modulus` is `0`, the behaviour is undefined.
static INLINE arith_u32 internal_mod_mul_u32(const arith_u32 multiplier, const arith_u32 multiplicand,
                                             const arith_u32 modulus) {
    return (arith_u32)(((arith_u64)multiplier * multiplicand) % modulus);
}

// Computes `(multiplier * multiplicand) % modulus`. If `modulus` is `0`, the behaviour is undefined.
static INLINE arith_u64 internal_mod_mul_u64(const arith_u64 multiplier, const arith_u64 multiplicand,
                                             const arith_u64 modulus) {
    const arith_u128 product = internal_multiply_u64(multiplier, multiplicand);

    return (arith_u64)(product % modulus);
}



#endif  // #ifndef ARITHMOS_NUMERIC_INTERNAL_H_
