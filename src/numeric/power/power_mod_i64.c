// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#include "arithmos/numeric/power.h"

#include <stdbool.h>

#include "numeric/numeric_internal.h"

#include "arithmos/core/types.h"



extern arith_i64 arith_power_mod_i64(const arith_i64 base, arith_u64 exponent, const arith_u64 modulus) {
    if (modulus == 1)
        return 0;

    arith_u64 unsigned_base = internal_unsigned_abs_i64(base);
    if (base < 0)
        unsigned_base = modulus - (unsigned_base % modulus);

    arith_u64 result = 1;

    if ((exponent & 1) == 1)
        result = unsigned_base % modulus;

    while (true) {
        if (exponent <= 1)
            return (arith_i64)result;

        do {
            unsigned_base = internal_mod_mul_u64(unsigned_base, unsigned_base, modulus);
            exponent >>= 1;
        } while ((exponent & 1) == 0);

        result = internal_mod_mul_u64(result, unsigned_base, modulus);
    }
}
