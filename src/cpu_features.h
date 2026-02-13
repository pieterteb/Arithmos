// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#ifndef ARITHMOS_CPU_FEATURES_H_
#define ARITHMOS_CPU_FEATURES_H_



#ifdef __BMI__
#    define ARITHMOS_CPU_HAS_BMI1 1
#else
#    define ARITHMOS_CPU_HAS_BMI1 0
#endif  // #ifdef __BMI__

#ifdef __BMI2__
#    define ARITHMOS_CPU_HAS_BMI2 1
#else
#    define ARITHMOS_CPU_HAS_BMI2 0
#endif  // #ifdef __BMI2__



#endif  // #ifndef ARITHMOS_CPU_FEATURES_H_
