// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/lcm.h"

#include <stdbool.h>

#include "bit_operations.h"
#include "expect.h"

#include "arithmos/core/types.h"



extern arith_u64 arith_lcm_u64(arith_u64 m, arith_u64 n) {
    // We use the identity:
    //
    //      lcm(m, n) = m * n / gcd(m, n)
    //


    if (m == 0 || n == 0)
        return 0;

    arith_u64 m_cpy       = m;
    const arith_u64 n_cpy = n;

    const unsigned i = internal_ctz_u64(m);
    m >>= i;
    const unsigned j = internal_ctz_u64(n);
    n >>= j;
    const unsigned k = (i < j) ? i : j;

    m_cpy >>= k;

    while (true) {
        const arith_u64 temp_n = n;
        const arith_u64 diff   = m - n;
        n                      = -diff;

        if (internal_unlikely(n == 0))
            break;

        if (m > temp_n) {
            m = temp_n;
            n = diff;
        }

        n >>= internal_ctz_u64(n);
    }

    return m_cpy / m * n_cpy;
}
