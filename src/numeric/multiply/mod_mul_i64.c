// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/multiply.h"

#include "arithmos/core/types.h"



extern arith_i64 arith_mod_mul_i64(const arith_i64 multiplier, const arith_i64 multiplicand, const arith_u64 modulus) {
    const arith_i128 signed_result = (arith_i128)multiplier * multiplicand % modulus;

    return (arith_i64)((signed_result < 0) ? signed_result + modulus : signed_result);
}
