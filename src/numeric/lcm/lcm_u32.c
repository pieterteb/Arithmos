// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/lcm.h"

#include <stdbool.h>

#include "bit_operations.h"
#include "expect.h"

#include "arithmos/core/types.h"



extern arith_u32 arith_lcm_u32(arith_u32 m, const arith_u32 n) {
    // See lcm_u64.c for implementation details.

    if (m == 0 || n == 0)
        return 0;

    const unsigned i = internal_ctz_u32(m);
    arith_u32 m_cpy  = m >> i;
    const unsigned j = internal_ctz_u32(n);
    arith_u32 n_cpy  = n >> j;
    const unsigned k = (i < j) ? i : j;

    m >>= k;

    while (true) {
        const arith_u32 temp_n = n_cpy;
        const arith_u32 diff   = m_cpy - n_cpy;
        n_cpy                  = -diff;

        if (internal_unlikely(n_cpy == 0))
            break;

        if (m_cpy > temp_n) {
            m_cpy = temp_n;
            n_cpy = diff;
        }

        n_cpy >>= internal_ctz_u32(n_cpy);
    }

    return m / m_cpy * n;
}
