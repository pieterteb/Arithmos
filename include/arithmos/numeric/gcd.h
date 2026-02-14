// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#ifndef ARITHMOS_NUMBER_LCM_H_
#define ARITHMOS_NUMBER_LCM_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "arithmos/core/types.h"



// Computes the greatest common devisor (gcd) of `m` and `n`. If both `m`
// and `n` are `0`, returns `0`. If `gcd(m, n)` is not representable as a
// value of type `arith_i32`, the behaviour is undefined.
arith_i32 arith_gcd_i32(const arith_i32 m, const arith_i32 n);

// Computes the greatest common devisor (gcd) of `m` and `n`. If both `m`
// and `n` are `0`, returns `0`. If `gcd(m, n)` is not representable as a
// value of type `arith_i64`, the behaviour is undefined.
arith_i64 arith_gcd_i64(const arith_i64 m, const arith_i64 n);

// Computes the greatest common devisor of `m` and `n`. If both `m` and `n`
// are `0`, returns `0`.
arith_u32 arith_gcd_u32(arith_u32 m, arith_u32 n);

// Computes the greatest common devisor of `m` and `n`. If both `m` and `n`
// are `0`, returns `0`.
arith_u64 arith_gcd_u64(arith_u64 m, arith_u64 n);



#ifdef __cplusplus
}
#endif

#endif  // #ifndef ARITHMOS_NUMBER_LCM_H_
