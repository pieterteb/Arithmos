// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/gcd.h"

#include <stdbool.h>

#include "bit_operations.h"
#include "expect.h"

#include "arithmos/core/types.h"



extern arith_u32 arith_gcd_u32(arith_u32 m, arith_u32 n) {
    // See gcd_u64.c for implementation details.

    if (m == 0)
        return n;

    if (n == 0)
        return m;

    const unsigned i = internal_ctz_u32(m);
    m >>= i;
    const unsigned j = internal_ctz_u32(n);
    n >>= j;
    const unsigned k = (i < j) ? i : j;

    while (true) {
        const arith_u32 n_cpy = n;
        const arith_u32 diff  = m - n;
        n                     = -diff;

        if (internal_unlikely(n == 0))
            return m << k;

        if (m > n_cpy) {
            m = n_cpy;
            n = diff;
        }

        n >>= internal_ctz_u32(n);
    }
}
