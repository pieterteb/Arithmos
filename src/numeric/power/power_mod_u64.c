// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/power.h"

#include <stdbool.h>

#include "numeric/numeric_internal.h"

#include "arithmos/core/types.h"



extern arith_u64 arith_power_mod_u64(arith_u64 base, arith_u64 exponent, const arith_u64 modulus) {
    // This function uses a similar algorithm as arith_power_u64() but with some extra
    // edge case checks and modular multiplication instead of regular multiplication.

    if (modulus == 1)
        return 0;

    arith_u64 result = 1;

    if ((exponent & 1) == 1)
        result = base % modulus;

    while (true) {
        if (exponent <= 1)
            return result;

        do {
            base = internal_mod_mul_u64(base, base, modulus);
            exponent >>= 1;
        } while ((exponent & 1) == 0);

        result = internal_mod_mul_u64(result, base, modulus);
    }
}
