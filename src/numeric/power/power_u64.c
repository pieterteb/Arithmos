// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/power.h"

#include <stdbool.h>

#include "arithmos/core/types.h"



extern arith_u64 arith_power_u64(arith_u64 base, arith_u64 exponent) {
    arith_u64 result = 1;

    while (true) {
        // We precompute result * base so that we can simply update result with a conditional move instead of creating a
        // new branch.
        const arith_u64 temp = result * base;
        result               = (exponent & 1) ? temp : result;

        // We do not need the bitshift if exponent <= 1 since it would be 0 afterwards.
        if (exponent <= 1)
            return result;

        exponent >>= 1;
        base *= base;
    }
}
