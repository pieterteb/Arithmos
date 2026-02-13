// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/abs.h"

#include "numeric/numeric_internal.h"

#include "arithmos/core/types.h"



extern arith_i32 arith_abs_i32(const arith_i32 x) {
    return internal_abs_i32(x);
}
