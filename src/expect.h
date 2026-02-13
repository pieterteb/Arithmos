// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pieter te Brake

#ifndef ARITHMOS_EXPECT_H_
#define ARITHMOS_EXPECT_H_


#include <stdbool.h>

#include "inline.h"



#ifndef __has_builtin
#    error "__has_builtin macro is required."
#endif  // #ifndef __has_builtin


// Returns `expression` that is likely to be true (90%).
static INLINE long internal_likely(const long expression) {
#if __has_builtin(__builtin_expect)
    return __builtin_expect(expression, 1);
#else
    return expression;
#endif  // #if __has_builtin(__builtin_expect)
}

// Returns `expression` that is likely to be false (90%).
static INLINE long internal_unlikely(const long expression) {
#if __has_builtin(__builtin_expect)
    return __builtin_expect(expression, 0);
#else
    return expression;
#endif  // #if __has_builtin(__builtin_expect)
}

// Returns `expression == value` where we expect this to be true (90%).
static INLINE long internal_expect(const long expression, const long value) {
#if __has_builtin(__builtin_expect)
    return __builtin_expect(expression, value);
#else
    return (long)(expression == value);
#endif  // #if __has_builtin(__builtin_expect)
}

#if __has_builtin(__builtin_expect_with_probability)
// Returns `expression` that is likely to be true with chance `probability`.
#    define internal_likely_with_probability(expression, probability) \
        __builtin_expect_with_probability(expression, 1, probability)

// Returns `expression` that is likely to be false with chance `probability`.
#    define internal_unlikely_with_probability(expression, probability) \
        __builtin_expect_with_probability(expression, 0, probability)

// Returns `expression == value` where we expect this to be true with chance `probability`.
#    define internal_expect_with_probability(expression, value, probability) \
        __builtin_expect_with_probability(expression, value, probability)
#else
// Returns `expression` that is likely to be true with chance `probability`.
#    define internal_likely_with_probability(expression, probability)        (expression)

// Returns `expression` that is likely to be false with chance `probability`.
#    define internal_unlikely_with_probability(expression, probability)      (expression)

// Returns `expression == value` where we expect this to be true with chance `probability`.
#    define internal_expect_with_probability(expression, value, probability) ((expression) == value)
#endif  //  __has_builtin(__builtin_expect_with_probability)



#endif  // #ifndef ARITHMOS_EXPECT_H_
