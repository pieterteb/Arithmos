// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#ifndef ARITHMOS_NUMERIC_MULTIPLY_H_
#define ARITHMOS_NUMERIC_MULTIPLY_H_


#include "arithmos/core/types.h"



// Computes `multiplier * multiplicand (mod modulus)`. If `modulus` is `0`, the behaviour is undefined.
// If `multiplier * multiplicand (mod modulus)` is not representable as a value of `arith_i32`, the
// behaviour is undefined (this case will not occur if `modulus <= ARITH_I32_MAX + 1`).
arith_i32 arith_mod_mul_i32(const arith_i32 multiplier, const arith_i32 multiplicand, const arith_u32 modulus);

// Computes `multiplier * multiplicand (mod modulus)`. If `modulus` is `0`, the behaviour is undefined.
// If `multiplier * multiplicand (mod modulus)` is not representable as a value of `arith_i64`, the
// behaviour is undefined (this case will not occur if `modulus <= ARITH_I64_MAX + 1`).
arith_i64 arith_mod_mul_i64(const arith_i64 multiplier, const arith_i64 multiplicand, const arith_u64 modulus);

// Computes `multiplier * multiplicand (mod modulus)`. If `modulus` is `0`, the behaviour is undefined.
arith_u32 arith_mod_mul_u32(const arith_u32 multiplier, const arith_u32 multiplicand, const arith_u32 modulus);

// Computes `multiplier * multiplicand (mod modulus)`. If `modulus` is `0`, the behaviour is undefined.
arith_u64 arith_mod_mul_u64(const arith_u64 multiplier, const arith_u64 multiplicand, const arith_u64 modulus);


// Computes `multiplier * multiplicand`, and returns it as an `arith_i128`.
arith_i128 arith_multiply_i64(const arith_i64 multiplier, const arith_i64 multiplicand);

// Computes `multiplier * multiplicand`, and returns it as an `arith_u128`.
arith_u128 arith_multiply_u64(const arith_u64 multiplier, const arith_u64 multiplicand);



#endif  // #ifndef ARITHMOS_NUMERIC_MULTIPLY_H_
