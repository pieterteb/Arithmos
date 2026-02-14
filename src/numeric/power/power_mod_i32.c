// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/power.h"

#include <stdbool.h>

#include "numeric/numeric_internal.h"

#include "arithmos/core/types.h"



extern arith_i32 arith_power_mod_i32(arith_i32 base, arith_u32 exponent, const arith_u32 modulus) {
    if (modulus == 1)
        return 0;

    arith_i32 result = 1;

    while (true) {
        if ((exponent & 1) == 1)
            result = internal_mod_mul_i32(result, base, modulus);

        if (exponent <= 1)
            return (result < 0) ? (arith_i32)((arith_i64)result + modulus) : result;

        exponent >>= 1;
        base = internal_mod_mul_i32(base, base, modulus);
    }
}
