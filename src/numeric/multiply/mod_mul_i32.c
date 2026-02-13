// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/multiply.h"

#include "arithmos/core/types.h"



extern arith_i32 arith_mod_mul_i32(const arith_i32 multiplier, const arith_i32 multiplicand, const arith_u32 modulus) {
    const arith_i64 signed_result = (arith_i64)multiplier * multiplicand % modulus;

    return (arith_i32)((signed_result < 0) ? signed_result + modulus : signed_result);
}
