#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "arithmos/core/limits.h"
#include "arithmos/numeric/gcd.h"



#define TEST(func, m, n, ans)                                                       \
    do {                                                                            \
        if (func(m, n) != ans) {                                                    \
            fprintf(stderr, "Failed test " #func "(" #m ", " #n ") == " #ans "\n"); \
            passed = false;                                                         \
        }                                                                           \
    } while (0)


int main(void) {
    bool passed = true;

    TEST(arith_gcd_i32, 0, 0, 0);
    TEST(arith_gcd_i32, 0, 7, 7);
    TEST(arith_gcd_i32, 5, 0, 5);
    TEST(arith_gcd_i32, 48, 18, 6);
    TEST(arith_gcd_i32, 101, 10, 1);
    TEST(arith_gcd_i32, 27, 9, 9);
    TEST(arith_gcd_i32, 123456, 789012, 12);
    TEST(arith_gcd_i32, ARITH_I32_MAX, ARITH_I32_MAX, ARITH_I32_MAX);
    TEST(arith_gcd_i32, ARITH_I32_MIN, ARITH_I32_MAX, 1);
    TEST(arith_gcd_i32, ARITH_I32_MIN, 6, 2);
    TEST(arith_gcd_i32, -48, 18, 6);
    TEST(arith_gcd_i32, 48, -18, 6);
    TEST(arith_gcd_i32, -48, -18, 6);

    TEST(arith_gcd_i64, 0, 0, 0);
    TEST(arith_gcd_i64, 0, 7, 7);
    TEST(arith_gcd_i64, 5, 0, 5);
    TEST(arith_gcd_i64, 48, 18, 6);
    TEST(arith_gcd_i64, 101, 10, 1);
    TEST(arith_gcd_i64, 27, 9, 9);
    TEST(arith_gcd_i64, 123456, 789012, 12);
    TEST(arith_gcd_i64, 1000000000, 2, 2);
    TEST(arith_gcd_i64, ARITH_I64_MAX, ARITH_I64_MAX, ARITH_I64_MAX);
    TEST(arith_gcd_i64, ARITH_I64_MIN, ARITH_I64_MAX, 1);
    TEST(arith_gcd_i64, ARITH_I64_MIN, 6, 2);
    TEST(arith_gcd_i64, -48, 18, 6);
    TEST(arith_gcd_i64, 48, -18, 6);
    TEST(arith_gcd_i64, -48, -18, 6);

    TEST(arith_gcd_u32, 0, 0, 0);
    TEST(arith_gcd_u32, 0, 7, 7);
    TEST(arith_gcd_u32, 5, 0, 5);
    TEST(arith_gcd_u32, 48, 18, 6);
    TEST(arith_gcd_u32, 101, 10, 1);
    TEST(arith_gcd_u32, 27, 9, 9);
    TEST(arith_gcd_u32, 123456, 789012, 12);
    TEST(arith_gcd_u32, ARITH_U32_MAX, ARITH_U32_MAX, ARITH_U32_MAX);

    TEST(arith_gcd_u64, 0, 0, 0);
    TEST(arith_gcd_u64, 0, 7, 7);
    TEST(arith_gcd_u64, 5, 0, 5);
    TEST(arith_gcd_u64, 48, 18, 6);
    TEST(arith_gcd_u64, 101, 10, 1);
    TEST(arith_gcd_u64, 27, 9, 9);
    TEST(arith_gcd_u64, 123456, 789012, 12);
    TEST(arith_gcd_u64, 1000000000, 2, 2);
    TEST(arith_gcd_u64, ARITH_U64_MAX, ARITH_U64_MAX, ARITH_U64_MAX);


    if (!passed)
        return 1;


    return 0;
}
