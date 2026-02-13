// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/multiply.h"

#include "numeric/numeric_internal.h"

#include "arithmos/core/types.h"



extern arith_u64 arith_mod_mul_u64(const arith_u64 multiplier, const arith_u64 multiplicand, const arith_u64 modulus) {
    return internal_mod_mul_u64(multiplier, multiplicand, modulus);
}
