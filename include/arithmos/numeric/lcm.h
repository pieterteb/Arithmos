// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#ifndef ARITHMOS_NUMBER_GCD_H_
#define ARITHMOS_NUMBER_GCD_H_


#include "arithmos/core/types.h"



// Computes least common multiple (lcm) of `m` and `n`. If `lcm(m, n)` is not representable
// as a value of type `arith_i32`, the behaviour is undefined.
arith_i32 arith_lcm_i32(const arith_i32 m, const arith_i32 n);

// Computes least common multiple (lcm) of `m` and `n`. If `lcm(m, n)` is not representable
// as a value of type `arith_i64`, the behaviour is undefined.
arith_i64 arith_lcm_i64(const arith_i64 m, const arith_i64 n);

// Computes least common multiple (lcm) of `m` and `n`. If `lcm(m, n)` is not
// representable as a value of type `arith_u32`, returns `lcm(m, n) (mod ARITH_U32_MAX + 1)`.
arith_u32 arith_lcm_u32(arith_u32 m, arith_u32 n);

// Computes least common multiple (lcm) of `m` and `n`. If `lcm(m, n)` is not
// representable as a value of type `arith_u64`, returns `lcm(m, n) (mod ARITH_U64_MAX + 1)`.
arith_u64 arith_lcm_u64(arith_u64 m, arith_u64 n);



#endif  // #ifndef ARITHMOS_NUMBER_GCD_H_
