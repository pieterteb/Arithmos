#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "arithmos/core/limits.h"
#include "arithmos/numeric/lcm.h"



#define TEST(func, m, n, ans)                                                       \
    do {                                                                            \
        if (func(m, n) != ans) {                                                    \
            fprintf(stderr, "Failed test " #func "(" #m ", " #n ") == " #ans "\n"); \
            passed = false;                                                         \
        }                                                                           \
    } while (0)


int main(void) {
    bool passed = true;

    TEST(arith_lcm_i32, 0, 0, 0);
    TEST(arith_lcm_i32, 0, 7, 0);
    TEST(arith_lcm_i32, 5, 0, 0);
    TEST(arith_lcm_i32, 4, 6, 12);
    TEST(arith_lcm_i32, 21, 6, 42);
    TEST(arith_lcm_i32, 13, 17, 221);
    TEST(arith_lcm_i32, 27, 9, 27);
    TEST(arith_lcm_i32, 1000000000, 2, 1000000000);
    TEST(arith_lcm_i32, ARITH_I32_MAX, ARITH_I32_MAX, ARITH_I32_MAX);
    TEST(arith_lcm_i32, -4, 6, 12);
    TEST(arith_lcm_i32, 4, -6, 12);
    TEST(arith_lcm_i32, -4, -6, 12);

    TEST(arith_lcm_i64, 0, 0, 0);
    TEST(arith_lcm_i64, 0, 7, 0);
    TEST(arith_lcm_i64, 5, 0, 0);
    TEST(arith_lcm_i64, 21, 6, 42);
    TEST(arith_lcm_i64, 13, 17, 221);
    TEST(arith_lcm_i64, 27, 9, 27);
    TEST(arith_lcm_i64, 1000000000, 2, 1000000000);
    TEST(arith_lcm_i64, 123456, 789012, 8117355456);
    TEST(arith_lcm_i64, ARITH_I64_MAX, ARITH_I64_MAX, ARITH_I64_MAX);
    TEST(arith_lcm_i64, -4, 6, 12);
    TEST(arith_lcm_i64, 4, -6, 12);
    TEST(arith_lcm_i64, -4, -6, 12);

    TEST(arith_lcm_u32, 0, 0, 0);
    TEST(arith_lcm_u32, 0, 7, 0);
    TEST(arith_lcm_u32, 5, 0, 0);
    TEST(arith_lcm_u32, 21, 6, 42);
    TEST(arith_lcm_u32, 13, 17, 221);
    TEST(arith_lcm_u32, 27, 9, 27);
    TEST(arith_lcm_u32, 1000000000, 2, 1000000000);
    TEST(arith_lcm_u32, ARITH_U32_MAX, ARITH_U32_MAX, ARITH_U32_MAX);

    TEST(arith_lcm_u64, 0, 0, 0);
    TEST(arith_lcm_u64, 0, 7, 0);
    TEST(arith_lcm_u64, 5, 0, 0);
    TEST(arith_lcm_u64, 21, 6, 42);
    TEST(arith_lcm_u64, 13, 17, 221);
    TEST(arith_lcm_u64, 27, 9, 27);
    TEST(arith_lcm_u64, 1000000000, 2, 1000000000);
    TEST(arith_lcm_u64, 123456, 789012, 8117355456);
    TEST(arith_lcm_u64, ARITH_U64_MAX, ARITH_U64_MAX, ARITH_U64_MAX);


    if (!passed)
        return 1;


    return 0;
}
