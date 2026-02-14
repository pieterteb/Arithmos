// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#ifndef ARITHMOS_NUMERIC_ABS_H_
#define ARITHMOS_NUMERIC_ABS_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "arithmos/core/types.h"



// Computes the absolute value of `x`. The behaviour is undefined if
// the result cannot be represented as a value of type `arith_i32`.
arith_i32 arith_abs_i32(const arith_i32 x);

// Computes the absolute value of `x`. The behaviour is undefined if
// the result cannot be represented as a value of type `arith_i64`.
arith_i64 arith_abs_i64(const arith_i64 x);

// Computes the absolute value of `x`, and returns it as an unsigned value.
arith_u32 arith_unsigned_abs_i32(const arith_i32 x);

// Computes the absolute value of `x`, and returns it as an unsigned value.
arith_u64 arith_unsigned_abs_i64(const arith_i64 x);



#ifdef __cplusplus
}
#endif

#endif  // #ifdef ARITHMOS_NUMERIC_ABS_H_
