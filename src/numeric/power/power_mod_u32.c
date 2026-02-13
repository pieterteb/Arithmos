// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/power.h"

#include <stdbool.h>

#include "numeric/numeric_internal.h"

#include "arithmos/core/types.h"



extern arith_u32 arith_power_mod_u32(arith_u32 base, arith_u32 exponent, const arith_u32 modulus) {
    if (modulus == 1)
        return 0;

    arith_u32 result = 1;

    if ((exponent & 1) == 1)
        result = base % modulus;

    while (true) {
        if (exponent <= 1)
            return result;

        do {
            base = internal_mod_mul_u32(base, base, modulus);
            exponent >>= 1;
        } while ((exponent & 1) == 0);

        result = internal_mod_mul_u32(result, base, modulus);
    }
}
