// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#ifndef ARITHMOS_NUMERIC_POWER_H_
#define ARITHMOS_NUMERIC_POWER_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "arithmos/core/types.h"



// Computes `base ^ exponent` where `^` is exponentiation. If both `base` and `exponent`
// are `0`, returns `1`. If `base ^ exponent` is not representable as a value of type
// `arith_i32`, the behaviour is undefined.
arith_i32 arith_power_i32(arith_i32 base, arith_u32 exponent);

// Computes `base ^ exponent` where `^` is exponentiation. If both `base` and `exponent`
// are `0`, returns `1`. If `base ^ exponent` is not representable as a value of type
// `arith_i64`, the behaviour is undefined.
arith_i64 arith_power_i64(arith_i64 base, arith_u64 exponent);

// Computes `base ^ exponent` where `^` is exponentiation. If both `base` and `exponent`
// are `0`, returns `1`. If `base ^ exponent` is not representable as a value of type
// `arith_u32`, returns the result modulo `ARITH_U32_MAX + 1`.
arith_u32 arith_power_u32(arith_u32 base, arith_u32 exponent);

// Computes `base ^ exponent` where `^` is exponentiation. If both `base` and `exponent`
// are `0`, returns `1`. If `base ^ exponent` is not representable as a value of type
// `arith_u64`, returns the result modulo `ARITH_U64_MAX + 1`.
arith_u64 arith_power_u64(arith_u64 base, arith_u64 exponent);


// Computes `base ^ exponent (mod modulus)` where `^` is exponentiation. If `modulus` is `0`,
// the behaviour is undefined. If both `base` and `exponent` are `0`, `base ^ exponent == 1`.
// If `base ^ exponent (mod modulus)` is not representable as a value of `arith_i32`, the
// behaviour is undefined (this case will not occur if `modulus <= ARITH_I32_MAX + 1`).
arith_i32 arith_power_mod_i32(const arith_i32 base, arith_u32 exponent, const arith_u32 modulus);

// Computes `base ^ exponent (mod modulus)` where `^` is exponentiation. If `modulus` is `0`,
// the behaviour is undefined. If both `base` and `exponent` are `0`, `base ^ exponent == 1`.
// If `base ^ exponent (mod modulus)` is not representable as a value of `arith_i64`, the
// behaviour is undefined (this case will not occur if `modulus <= ARITH_I64_MAX + 1`).
// Note that `arith_power_mod_i32()` is considerably faster than `arith_power_mod_i64()`.
arith_i64 arith_power_mod_i64(arith_i64 base, arith_u64 exponent, const arith_u64 modulus);

// Computes `base ^ exponent (mod modulus)` where `^` is exponentiation. If `modulus` is `0`,
// the behaviour is undefined. If both `base` and `exponent` are `0`, `base ^ exponent == 1`.
arith_u32 arith_power_mod_u32(const arith_u32 base, arith_u32 exponent, const arith_u32 modulus);

// Computes `base ^ exponent (mod modulus)` where `^` is exponentiation. If `modulus` is `0`,
// the behaviour is undefined. If both `base` and `exponent` are `0`, `base ^ exponent == 1`.
// Note that `arith_power_mod_u32()` is considerably faster than `arith_power_mod_u64()`.
arith_u64 arith_power_mod_u64(const arith_u64 base, arith_u64 exponent, const arith_u64 modulus);



#ifdef __cplusplus
}
#endif

#endif  // #ifndef ARITHMOS_NUMERIC_POWER_H_
