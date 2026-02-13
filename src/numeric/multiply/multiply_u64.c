// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/multiply.h"

#include "numeric/numeric_internal.h"

#include "arithmos/core/types.h"



extern arith_u128 arith_multiply_u64(const arith_u64 multiplier, const arith_u64 multiplicand) {
    return internal_multiply_u64(multiplier, multiplicand);
}
