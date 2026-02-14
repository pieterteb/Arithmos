// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#ifndef ARITHMOS_CORE_TYPES_H_
#define ARITHMOS_CORE_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>



typedef int32_t arith_i32;
typedef uint32_t arith_u32;

typedef int64_t arith_i64;
typedef uint64_t arith_u64;

typedef __int128_t arith_i128;
typedef __uint128_t arith_u128;



#ifdef __cplusplus
}
#endif

#endif  // #ifndef ARITHMOS_CORE_TYPES_H_
