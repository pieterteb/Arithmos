// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/lcm.h"

#include <stdbool.h>

#include "bit_operations.h"
#include "expect.h"

#include "arithmos/core/types.h"



extern arith_u32 arith_lcm_u32(arith_u32 m, arith_u32 n) {
    // See lcm_u64.c for implementation details.

    if (m == 0 || n == 0)
        return 0;

    arith_u32 m_cpy       = m;
    const arith_u32 n_cpy = n;

    const unsigned i = internal_ctz_u32(m);
    m >>= i;
    const unsigned j = internal_ctz_u32(n);
    n >>= j;
    const unsigned k = (i < j) ? i : j;

    m_cpy >>= k;

    while (true) {
        const arith_u32 temp_n = n;
        const arith_u32 diff   = m - n;
        n                      = -diff;

        if (internal_unlikely(n == 0))
            break;

        if (m > temp_n) {
            m = temp_n;
            n = diff;
        }

        n >>= internal_ctz_u32(n);
    }

    return m_cpy / m * n_cpy;
}
