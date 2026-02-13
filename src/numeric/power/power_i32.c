// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/power.h"

#include <stdbool.h>

#include "arithmos/core/types.h"



extern arith_i32 arith_power_i32(arith_i32 base, arith_u32 exponent) {
    // See power_u64.c for implementation details.

    arith_i32 result = 1;

    while (true) {
        const arith_i32 temp = result * base;
        result               = (exponent & 1) ? temp : result;

        if (exponent <= 1)
            return result;

        exponent >>= 1;
        base *= base;
    }
}
