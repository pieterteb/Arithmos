#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "arithmos/core/limits.h"
#include "arithmos/numeric/multiply.h"



#define TEST(func, m, n, ans)                                                       \
    do {                                                                            \
        if (func(m, n) != ans) {                                                    \
            fprintf(stderr, "Failed test " #func "(" #m ", " #n ") == " #ans "\n"); \
            passed = false;                                                         \
        }                                                                           \
    } while (0)

#define TEST_MOD(func, a, b, m, ans)                                                        \
    do {                                                                                    \
        if (func(a, b, m) != ans) {                                                         \
            fprintf(stderr, "Failed test " #func "(" #a ", " #b ", " #m ") == " #ans "\n"); \
            passed = false;                                                                 \
        }                                                                                   \
    } while (0)


int main(void) {
    bool passed = true;

    TEST_MOD(arith_mod_mul_i32, 3, 4, 5, 2);
    TEST_MOD(arith_mod_mul_i32, -3, 4, 5, 3);
    TEST_MOD(arith_mod_mul_i32, 3, -4, 5, 3);
    TEST_MOD(arith_mod_mul_i32, -3, -4, 5, 2);
    TEST_MOD(arith_mod_mul_i32, 0, 4, 5, 0);
    TEST_MOD(arith_mod_mul_i32, 3, 0, 5, 0);
    TEST_MOD(arith_mod_mul_i32, 3, 4, 1, 0);
    TEST_MOD(arith_mod_mul_i32, ARITH_I32_MAX, ARITH_I32_MAX, 1000000, 420609);
    TEST_MOD(arith_mod_mul_i32, ARITH_I32_MIN, ARITH_I32_MAX, 1000000, 95744);

    TEST_MOD(arith_mod_mul_i64, 3, 4, 5, 2);
    TEST_MOD(arith_mod_mul_i64, -3, 4, 5, 3);
    TEST_MOD(arith_mod_mul_i64, 3, -4, 5, 3);
    TEST_MOD(arith_mod_mul_i64, -3, -4, 5, 2);
    TEST_MOD(arith_mod_mul_i64, 0, 4, 5, 0);
    TEST_MOD(arith_mod_mul_i64, 3, 0, 5, 0);
    TEST_MOD(arith_mod_mul_i64, 3, 4, 1, 0);
    TEST_MOD(arith_mod_mul_i64, ARITH_I64_MAX, ARITH_I64_MAX, 1000000, 501249);
    TEST_MOD(arith_mod_mul_i64, ARITH_I64_MIN, ARITH_I64_MAX, 1000000, 722944);

    TEST_MOD(arith_mod_mul_u32, 3, 4, 5, 2);
    TEST_MOD(arith_mod_mul_u32, 0, 4, 5, 0);
    TEST_MOD(arith_mod_mul_u32, 3, 0, 5, 0);
    TEST_MOD(arith_mod_mul_u32, 3, 4, 1, 0);
    TEST_MOD(arith_mod_mul_u32, ARITH_U32_MAX, ARITH_U32_MAX, 1000000, 617025);

    TEST_MOD(arith_mod_mul_u64, 3, 4, 5, 2);
    TEST_MOD(arith_mod_mul_u64, 0, 4, 5, 0);
    TEST_MOD(arith_mod_mul_u64, 3, 0, 5, 0);
    TEST_MOD(arith_mod_mul_u64, 3, 4, 1, 0);
    TEST_MOD(arith_mod_mul_u64, ARITH_U64_MAX, ARITH_U64_MAX, 1000000, 108225);


    TEST(arith_multiply_i64, 5, 4, 20);
    TEST(arith_multiply_i64, -5, 4, -20);
    TEST(arith_multiply_i64, 5, -4, -20);
    TEST(arith_multiply_i64, -5, -4, 20);
    TEST(arith_multiply_i64, 0, 4, 0);
    TEST(arith_multiply_i64, ARITH_I64_MAX, ARITH_I64_MAX, (arith_i128)ARITH_I64_MAX * ARITH_I64_MAX);
    TEST(arith_multiply_i64, ARITH_I64_MIN, ARITH_I64_MAX, (arith_i128)ARITH_I64_MIN * ARITH_I64_MAX);

    TEST(arith_multiply_u64, 5, 4, 20);
    TEST(arith_multiply_u64, 0, 4, 0);
    TEST(arith_multiply_u64, ARITH_U64_MAX, ARITH_U64_MAX, (arith_u128)ARITH_U64_MAX * ARITH_U64_MAX);


    if (!passed)
        return 1;

    return 0;
}
