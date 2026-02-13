// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/gcd.h"

#include <stdbool.h>

#include "bit_operations.h"
#include "expect.h"
#include "numeric/numeric_internal.h"

#include "arithmos/core/types.h"



extern arith_i64 arith_gcd_i64(const arith_i64 m, const arith_i64 n) {
    // See gcd_u64.c for implementation details.

    arith_u64 un = internal_unsigned_abs_i64(n);
    if (m == 0)
        return (arith_i64)un;

    arith_u64 um = internal_unsigned_abs_i64(m);
    if (n == 0)
        return (arith_i64)um;

    const unsigned i = internal_ctz_u64(um);
    um >>= i;
    const unsigned j = internal_ctz_u64(un);
    un >>= j;
    const unsigned k = (i < j) ? i : j;

    while (true) {
        const arith_u64 un_cpy = un;
        const arith_u64 diff   = um - un;
        un                     = -diff;

        if (internal_unlikely(un == 0))
            return (arith_i64)(um << k);

        if (um > un_cpy) {
            um = un_cpy;
            un = diff;
        }

        un >>= internal_ctz_u64(un);
    }
}
