// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/lcm.h"

#include <stdbool.h>

#include "bit_operations.h"
#include "expect.h"
#include "numeric/numeric_internal.h"

#include "arithmos/core/types.h"



extern arith_i64 arith_lcm_i64(const arith_i64 m, const arith_i64 n) {
    // See lcm_u64.c for implementation details.

    if (m == 0 || n == 0)
        return 0;

    arith_u64 um       = internal_unsigned_abs_i64(m);
    const arith_u64 un = internal_unsigned_abs_i64(n);

    const unsigned i = internal_ctz_u64(um);
    arith_u64 um_cpy = um >> i;
    const unsigned j = internal_ctz_u64(un);
    arith_u64 un_cpy = un >> j;
    const unsigned k = (i < j) ? i : j;

    um >>= k;

    while (true) {
        const arith_u64 temp_n = un_cpy;
        const arith_u64 diff   = um_cpy - un_cpy;
        un_cpy                 = -diff;

        if (internal_unlikely(un_cpy == 0))
            break;

        if (um_cpy > temp_n) {
            um_cpy = temp_n;
            un_cpy = diff;
        }

        un_cpy >>= internal_ctz_u64(un_cpy);
    }

    return (arith_i64)(um / um_cpy * un);
}
