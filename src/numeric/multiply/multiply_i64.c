// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/multiply.h"

#include "arithmos/core/types.h"



extern arith_i128 arith_multiply_i64(const arith_i64 multiplier, const arith_i64 multiplicand) {
    return (arith_i128)multiplier * multiplicand;
}
