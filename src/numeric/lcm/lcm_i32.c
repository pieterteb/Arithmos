// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/lcm.h"

#include <stdbool.h>

#include "bit_operations.h"
#include "expect.h"
#include "numeric/numeric_internal.h"

#include "arithmos/core/types.h"



extern arith_i32 arith_lcm_i32(const arith_i32 m, const arith_i32 n) {
    // See lcm_u64.c for implementation details.

    if (m == 0 || n == 0)
        return 0;

    arith_u32 um = internal_unsigned_abs_i32(m);
    arith_u32 un = internal_unsigned_abs_i32(n);

    arith_u32 um_cpy       = um;
    const arith_u32 un_cpy = un;

    const unsigned i = internal_ctz_u32(um);
    um >>= i;
    const unsigned j = internal_ctz_u32(un);
    un >>= j;
    const unsigned k = (i < j) ? i : j;

    um_cpy >>= k;

    while (true) {
        const arith_u32 temp_n = un;
        const arith_u32 diff   = um - un;
        un                     = -diff;

        if (internal_unlikely(un == 0))
            break;

        if (um > temp_n) {
            um = temp_n;
            un = diff;
        }

        un >>= internal_ctz_u32(un);
    }

    return (arith_i32)(um_cpy / um * un_cpy);
}
