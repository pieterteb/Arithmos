// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/gcd.h"

#include <stdbool.h>

#include "bit_operations.h"
#include "expect.h"

#include "arithmos/core/types.h"



extern arith_u64 arith_gcd_u64(arith_u64 m, arith_u64 n) {
    // The GCD is computed using the binary GCD algorithm. One can verify that
    //
    //     gcd(m, n) = m,                  if n = 0                    (1)
    //     gcd(2m, 2n) = 2 * gcd(m, n),    so 2 is a common devisor    (2)
    //     gcd(m, 2n) = gcd(m, n),         if m is odd                 (3)
    //     gcd(m, n) = gcd(m, n - m),      if m, n odd and m <= n.     (4)
    //
    // We start by applying (2) for the greatest common power of 2. Now we know that at least one of m and n is odd. If
    // we apply (3), both m and n are odd so (4) can be applied. Therefore, by repeating (3) and (4), we eventually
    // reach a situation like (1), where we can return.
    //
    // The time complexity of this implementation is O(log(min(m, n))).


    if (m == 0)
        return n;

    if (n == 0)
        return m;

    const unsigned i = internal_ctz_u64(m);
    m >>= i;
    const unsigned j = internal_ctz_u64(n);
    n >>= j;
    const unsigned k = (i < j) ? i : j;

    while (true) {
        // We use a trick here, where we compute both m - n (stored in diff) and n - m (stored in n). This way, if
        // m > n at the start of the loop, we simply need two conditional move instructions instead of creating a new
        // branch, which drastically reduces branch predicition misses.

        const arith_u64 n_cpy = n;
        const arith_u64 diff  = m - n;
        n                     = -diff;

        if (internal_unlikely(n == 0))
            return m << k;

        if (m > n_cpy) {
            m = n_cpy;
            n = diff;
        }

        n >>= internal_ctz_u64(n);
    }
}
