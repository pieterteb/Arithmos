#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "arithmos/core/limits.h"
#include "arithmos/numeric/abs.h"



#define TEST(func, x, ans)                                                  \
    do {                                                                    \
        if (func(x) != ans) {                                               \
            fprintf(stderr, "Failed test " #func "(" #x ") == " #ans "\n"); \
            passed = false;                                                 \
        }                                                                   \
    } while (0)


int main(void) {
    bool passed = true;

    TEST(arith_abs_i32, 0, 0);
    TEST(arith_abs_i32, -10, 10);
    TEST(arith_abs_i32, 10, 10);
    TEST(arith_abs_i32, ARITH_I32_MIN + 1, ARITH_I32_MAX);
    TEST(arith_abs_i32, ARITH_I32_MAX, ARITH_I32_MAX);

    TEST(arith_abs_i64, 0, 0);
    TEST(arith_abs_i64, -10, 10);
    TEST(arith_abs_i64, 10, 10);
    TEST(arith_abs_i64, ARITH_I64_MIN + 1, ARITH_I64_MAX);
    TEST(arith_abs_i64, ARITH_I64_MAX, ARITH_I64_MAX);

    TEST(arith_unsigned_abs_i32, 0, 0);
    TEST(arith_unsigned_abs_i32, -10, 10);
    TEST(arith_unsigned_abs_i32, 10, 10);
    TEST(arith_unsigned_abs_i32, ARITH_I32_MIN, (arith_u32)ARITH_I32_MAX + 1);
    TEST(arith_unsigned_abs_i32, ARITH_I32_MAX, ARITH_I32_MAX);

    TEST(arith_unsigned_abs_i64, 0, 0);
    TEST(arith_unsigned_abs_i64, -10, 10);
    TEST(arith_unsigned_abs_i64, 10, 10);
    TEST(arith_unsigned_abs_i64, ARITH_I64_MIN, (arith_u64)ARITH_I64_MAX + 1);
    TEST(arith_unsigned_abs_i64, ARITH_I64_MAX, ARITH_I64_MAX);

    if (!passed)
        return 1;

    return 0;
}
