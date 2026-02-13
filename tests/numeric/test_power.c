#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "arithmos/core/limits.h"
#include "arithmos/numeric/power.h"



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

    TEST(arith_power_i32, 0, 0, 1);
    TEST(arith_power_i32, 5, 0, 1);
    TEST(arith_power_i32, 12345678, 0, 1);
    TEST(arith_power_i32, 0, 1, 0);
    TEST(arith_power_i32, 0, 10, 0);
    TEST(arith_power_i32, 1, 1000, 1);
    TEST(arith_power_i32, 1000, 1, 1000);
    TEST(arith_power_i32, 2, 10, 1024);
    TEST(arith_power_i32, 5, 3, 125);
    TEST(arith_power_i32, 2, 30, 1 << 30);
    TEST(arith_power_i32, -2, 3, -8);
    TEST(arith_power_i32, -3, 4, 81);
    TEST(arith_power_i32, -2, 31, ARITH_I32_MIN);

    TEST(arith_power_i64, 0, 0, 1);
    TEST(arith_power_i64, 5, 0, 1);
    TEST(arith_power_i64, 12345678, 0, 1);
    TEST(arith_power_i64, 0, 1, 0);
    TEST(arith_power_i64, 0, 10, 0);
    TEST(arith_power_i64, 1, 1000, 1);
    TEST(arith_power_i64, 1000, 1, 1000);
    TEST(arith_power_i64, 2, 10, 1024);
    TEST(arith_power_i64, 5, 3, 125);
    TEST(arith_power_i64, 2, 62, (arith_i64)1 << 62);
    TEST(arith_power_i64, -2, 3, -8);
    TEST(arith_power_i64, -3, 4, 81);
    TEST(arith_power_i64, -2, 63, ARITH_I64_MIN);

    TEST(arith_power_u32, 0, 0, 1);
    TEST(arith_power_u32, 5, 0, 1);
    TEST(arith_power_u32, 12345678, 0, 1);
    TEST(arith_power_u32, 0, 1, 0);
    TEST(arith_power_u32, 0, 10, 0);
    TEST(arith_power_u32, 1, 1000, 1);
    TEST(arith_power_u32, 1000, 1, 1000);
    TEST(arith_power_u32, 2, 10, 1024);
    TEST(arith_power_u32, 5, 3, 125);
    TEST(arith_power_u32, 2, 31, (arith_u32)1 << 31);
    TEST(arith_power_u32, 2, 32, 0);

    TEST(arith_power_u64, 0, 0, 1);
    TEST(arith_power_u64, 5, 0, 1);
    TEST(arith_power_u64, 12345678, 0, 1);
    TEST(arith_power_u64, 0, 1, 0);
    TEST(arith_power_u64, 0, 10, 0);
    TEST(arith_power_u64, 1, 1000, 1);
    TEST(arith_power_u64, 1000, 1, 1000);
    TEST(arith_power_u64, 2, 10, 1024);
    TEST(arith_power_u64, 5, 3, 125);
    TEST(arith_power_u64, 2, 63, (arith_u64)1 << 63);
    TEST(arith_power_u64, 2, 64, 0);


    TEST_MOD(arith_power_mod_i32, 0, 0, 1, 0);
    TEST_MOD(arith_power_mod_i32, 0, 0, 2, 1);
    TEST_MOD(arith_power_mod_i32, 5, 0, 7, 1);
    TEST_MOD(arith_power_mod_i32, 1, 12345, 97, 1);
    TEST_MOD(arith_power_mod_i32, 123, 456, 1, 0);
    TEST_MOD(arith_power_mod_i32, 14, 5, 7, 0);
    TEST_MOD(arith_power_mod_i32, 42, 1, 97, 42);
    TEST_MOD(arith_power_mod_i32, 2, 1000000, 13, 3);
    TEST_MOD(arith_power_mod_i32, 3, 1 << 20, 17, 1);
    TEST_MOD(arith_power_mod_i32, 5, 1000000007, 19, 4);
    TEST_MOD(arith_power_mod_i32, ARITH_I32_MAX, 2, 97, 54);
    TEST_MOD(arith_power_mod_i32, ARITH_I32_MIN, ARITH_I32_MAX, ARITH_I32_MAX - 1, 2147483518);
    TEST_MOD(arith_power_mod_i32, ARITH_I32_MAX, ARITH_I32_MAX, 5, 3);
    TEST_MOD(arith_power_mod_i32, 7, 1000, ARITH_I32_MAX - 1, 126036043);
    TEST_MOD(arith_power_mod_i32, -2, 3, 5, 2);
    TEST_MOD(arith_power_mod_i32, -2, 4, 5, 1);
    TEST_MOD(arith_power_mod_i32, -1, 12345, 97, 96);
    TEST_MOD(arith_power_mod_i32, -1, 12344, 97, 1);

    TEST_MOD(arith_power_mod_i64, 0, 0, 1, 0);
    TEST_MOD(arith_power_mod_i64, 0, 0, 2, 1);
    TEST_MOD(arith_power_mod_i64, 5, 0, 7, 1);
    TEST_MOD(arith_power_mod_i64, 1, 12345, 97, 1);
    TEST_MOD(arith_power_mod_i64, 123, 456, 1, 0);
    TEST_MOD(arith_power_mod_i64, 14, 5, 7, 0);
    TEST_MOD(arith_power_mod_i64, 42, 1, 97, 42);
    TEST_MOD(arith_power_mod_i64, 2, 1000000, 13, 3);
    TEST_MOD(arith_power_mod_i64, 3, 1 << 20, 17, 1);
    TEST_MOD(arith_power_mod_i64, 5, 1000000007, 19, 4);
    TEST_MOD(arith_power_mod_i64, ARITH_I64_MAX, 2, 97, 70);
    TEST_MOD(arith_power_mod_i64, ARITH_I64_MIN, ARITH_I64_MAX, ARITH_I64_MAX - 1, 9223372036854775678);
    TEST_MOD(arith_power_mod_i64, ARITH_I64_MAX, ARITH_I64_MAX, 5, 3);
    TEST_MOD(arith_power_mod_i64, 7, 1000, ARITH_I64_MAX - 1, 2360938972764976159);
    TEST_MOD(arith_power_mod_i64, -2, 3, 5, 2);
    TEST_MOD(arith_power_mod_i64, -2, 4, 5, 1);
    TEST_MOD(arith_power_mod_i64, -1, 12345, 97, 96);
    TEST_MOD(arith_power_mod_i64, -1, 12344, 97, 1);

    TEST_MOD(arith_power_mod_u32, 0, 0, 1, 0);
    TEST_MOD(arith_power_mod_u32, 0, 0, 2, 1);
    TEST_MOD(arith_power_mod_u32, 5, 0, 7, 1);
    TEST_MOD(arith_power_mod_u32, 1, 12345, 97, 1);
    TEST_MOD(arith_power_mod_u32, 123, 456, 1, 0);
    TEST_MOD(arith_power_mod_u32, 14, 5, 7, 0);
    TEST_MOD(arith_power_mod_u32, 42, 1, 97, 42);
    TEST_MOD(arith_power_mod_u32, 2, 1000000, 13, 3);
    TEST_MOD(arith_power_mod_u32, 3, 1 << 20, 17, 1);
    TEST_MOD(arith_power_mod_u32, 5, 1000000007, 19, 4);
    TEST_MOD(arith_power_mod_u32, ARITH_U32_MAX, 2, 97, 89);
    TEST_MOD(arith_power_mod_u32, ARITH_U32_MAX, ARITH_U32_MAX, ARITH_U32_MAX - 1, 1);
    TEST_MOD(arith_power_mod_u32, ARITH_U32_MAX, ARITH_U32_MAX, 13, 5);
    TEST_MOD(arith_power_mod_u32, 7, 1000, ARITH_U32_MAX - 1, 3918507799);

    TEST_MOD(arith_power_mod_u64, 0, 0, 1, 0);
    TEST_MOD(arith_power_mod_u64, 0, 0, 2, 1);
    TEST_MOD(arith_power_mod_u64, 5, 0, 7, 1);
    TEST_MOD(arith_power_mod_u64, 1, 12345, 97, 1);
    TEST_MOD(arith_power_mod_u64, 123, 456, 1, 0);
    TEST_MOD(arith_power_mod_u64, 14, 5, 7, 0);
    TEST_MOD(arith_power_mod_u64, 42, 1, 97, 42);
    TEST_MOD(arith_power_mod_u64, 2, 1000000, 13, 3);
    TEST_MOD(arith_power_mod_u64, 3, 1 << 20, 17, 1);
    TEST_MOD(arith_power_mod_u64, 5, 1000000007, 19, 4);
    TEST_MOD(arith_power_mod_u64, ARITH_U64_MAX, 2, 97, 11);
    TEST_MOD(arith_power_mod_u64, ARITH_U64_MAX, ARITH_U64_MAX, ARITH_U64_MAX - 1, 1);
    TEST_MOD(arith_power_mod_u64, ARITH_U64_MAX, ARITH_U64_MAX, 13, 8);
    TEST_MOD(arith_power_mod_u64, 7, 1000, ARITH_U64_MAX - 1, 16134194563271013985ULL);


    if (!passed)
        return 1;


    return 0;
}
