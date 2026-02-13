// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/gcd.h"

#include <stdbool.h>

#include "bit_operations.h"
#include "expect.h"
#include "numeric/numeric_internal.h"

#include "arithmos/core/types.h"



extern arith_i32 arith_gcd_i32(const arith_i32 m, const arith_i32 n) {
    // See gcd_u64.c for implementation details.

    arith_u32 un = internal_unsigned_abs_i32(n);
    if (m == 0)
        return (arith_i32)un;

    arith_u32 um = internal_unsigned_abs_i32(m);
    if (n == 0)
        return (arith_i32)um;

    const unsigned i = internal_ctz_u32(um);
    um >>= i;
    const unsigned j = internal_ctz_u32(un);
    un >>= j;
    const unsigned k = (i < j) ? i : j;

    while (true) {
        const arith_u32 un_cpy = un;
        const arith_u32 diff   = um - un;
        un                     = -diff;

        if (internal_unlikely(un == 0))
            return (arith_i32)(um << k);

        if (um > un_cpy) {
            um = un_cpy;
            un = diff;
        }

        un >>= internal_ctz_u32(un);
    }
}
