// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/power.h"

#include <stdbool.h>

#include "arithmos/core/types.h"



extern arith_u32 arith_power_u32(arith_u32 base, arith_u32 exponent) {
    // See power_u64.c for implementation details.

    arith_u32 result = 1;

    while (true) {
        const arith_u32 temp = result * base;
        result               = (exponent & 1) ? temp : result;

        if (exponent <= 1)
            return result;

        exponent >>= 1;
        base *= base;
    }
}
