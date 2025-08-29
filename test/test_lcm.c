#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#include "arithmos/number_theory.h"

int main() {
    long long res_ll;
    unsigned long long res_ull;
    bool overflow;

    assert(arithmos_lcmll(0, 0) == 0);
    assert(arithmos_lcmll(0, 5) == 0);
    assert(arithmos_lcmll(5, 0) == 0);
    assert(arithmos_lcmll(1, 1) == 1);
    assert(arithmos_lcmll(12, 12) == 12);
    assert(arithmos_lcmll(13, 17) == 221);
    assert(arithmos_lcmll(4, 12) == 12);
    assert(arithmos_lcmll(12, 4) == 12);
    assert(arithmos_lcmll(6, 8) == 24);
    assert(arithmos_lcmll(100, 80) == 400);
    assert(arithmos_lcmll(-1, 1) == 1);
    assert(arithmos_lcmll(1, -1) == 1);
    assert(arithmos_lcmll(-10, -20) == 20);
    assert(arithmos_lcmll(-12, -12) == 12);
    assert(arithmos_lcmll(LLONG_MAX, 1) == LLONG_MAX);
    assert(arithmos_lcmll(LLONG_MIN, 1) == LLONG_MIN);
    assert(arithmos_lcmll(LLONG_MAX, 2) == -2);
    
    const long long half_ll_max = LLONG_MAX / 2;

    overflow = arithmos_lcmll_safe(0, 0, &res_ll);
    assert(res_ll == 0 && overflow == false);
    overflow = arithmos_lcmll_safe(0, 5, &res_ll);
    assert(res_ll == 0 && overflow == false);
    overflow = arithmos_lcmll_safe(-10, -20, &res_ll);
    assert(res_ll == 20 && overflow == false);
    overflow = arithmos_lcmll_safe(6, 8, &res_ll);
    assert(overflow == false && res_ll == 24);
    overflow = arithmos_lcmll_safe(100, 80, &res_ll);
    assert(overflow == false && res_ll == 400);
    overflow = arithmos_lcmll_safe(half_ll_max, 4, &res_ll);
    assert(overflow == true);
    overflow = arithmos_lcmll_safe(1LL << 33, (1LL << 33) + 1, &res_ll);
    assert(overflow == true);
    overflow = arithmos_lcmll_safe(LLONG_MIN, 1, &res_ll);
    assert(overflow == true && res_ll == LLONG_MIN);
    overflow = arithmos_lcmll_safe(LLONG_MAX, 2, &res_ll);
    assert(overflow == true && res_ll == -2);

    assert(arithmos_lcmull(0, 0) == 0);
    assert(arithmos_lcmull(0, 5) == 0);
    assert(arithmos_lcmull(5, 0) == 0);
    assert(arithmos_lcmull(1, 1) == 1);
    assert(arithmos_lcmull(12, 12) == 12);
    assert(arithmos_lcmull(13, 17) == 221);
    assert(arithmos_lcmull(4, 12) == 12);
    assert(arithmos_lcmull(12, 4) == 12);
    assert(arithmos_lcmull(6, 8) == 24);
    assert(arithmos_lcmull(100, 80) == 400);
    assert(arithmos_lcmull(ULLONG_MAX, 1) == ULLONG_MAX);

    const long long half_ull_max = ULLONG_MAX / 2;

    overflow = arithmos_lcmull_safe(0, 0, &res_ull);
    assert(res_ull == 0 && overflow == false);
    overflow = arithmos_lcmull_safe(0, 5, &res_ull);
    assert(res_ull == 0 && overflow == false);
    overflow = arithmos_lcmull_safe(10, 20, &res_ull);
    assert(res_ull == 20 && overflow == false);
    overflow = arithmos_lcmull_safe(6, 8, &res_ull);
    assert(overflow == false && res_ull == 24);
    overflow = arithmos_lcmull_safe(100, 80, &res_ull);
    assert(overflow == false && res_ull == 400);
    overflow = arithmos_lcmull_safe(half_ull_max, 4, &res_ull);
    assert(overflow == true);
    overflow = arithmos_lcmull_safe(1LL << 33, (1LL << 33) + 1, &res_ull);
    assert(overflow == true && res_ull == 8589934592);

    assert(arithmos_lcmll_fast(0, 0) == 0);
    assert(arithmos_lcmll_fast(0, 5) == 0);
    assert(arithmos_lcmll_fast(5, 0) == 0);
    assert(arithmos_lcmll_fast(1, 1) == 1);
    assert(arithmos_lcmll_fast(12, 12) == 12);
    assert(arithmos_lcmll_fast(13, 17) == 221);
    assert(arithmos_lcmll_fast(4, 12) == 12);
    assert(arithmos_lcmll_fast(12, 4) == 12);
    assert(arithmos_lcmll_fast(6, 8) == 24);
    assert(arithmos_lcmll_fast(100, 80) == 400);
    assert(arithmos_lcmll_fast(-1, 1) == 1);
    assert(arithmos_lcmll_fast(1, -1) == 1);
    assert(arithmos_lcmll_fast(-10, -20) == 20);
    assert(arithmos_lcmll_fast(-12, -12) == 12);
    assert(arithmos_lcmll_fast(LLONG_MAX, 1) == LLONG_MAX);
    assert(arithmos_lcmll_fast(LLONG_MIN, 1) == LLONG_MIN);
    assert(arithmos_lcmll_fast(LLONG_MAX, 2) == -2);
    
    overflow = arithmos_lcmll_fast_safe(0, 0, &res_ll);
    assert(res_ll == 0 && overflow == false);
    overflow = arithmos_lcmll_fast_safe(0, 5, &res_ll);
    assert(res_ll == 0 && overflow == false);
    overflow = arithmos_lcmll_fast_safe(-10, -20, &res_ll);
    assert(res_ll == 20 && overflow == false);
    overflow = arithmos_lcmll_fast_safe(6, 8, &res_ll);
    assert(overflow == false && res_ll == 24);
    overflow = arithmos_lcmll_fast_safe(100, 80, &res_ll);
    assert(overflow == false && res_ll == 400);
    overflow = arithmos_lcmll_fast_safe(half_ll_max, 4, &res_ll);
    assert(overflow == true);
    overflow = arithmos_lcmll_fast_safe(1LL << 33, (1LL << 33) + 1, &res_ll);
    assert(overflow == true);
    overflow = arithmos_lcmll_safe(LLONG_MIN, 1, &res_ll);
    assert(overflow == true && res_ll == LLONG_MIN);
    overflow = arithmos_lcmll_safe(LLONG_MAX, 2, &res_ll);
    assert(overflow == true && res_ll == -2);

    assert(arithmos_lcmull_fast(0, 0) == 0);
    assert(arithmos_lcmull_fast(0, 5) == 0);
    assert(arithmos_lcmull_fast(5, 0) == 0);
    assert(arithmos_lcmull_fast(1, 1) == 1);
    assert(arithmos_lcmull_fast(12, 12) == 12);
    assert(arithmos_lcmull_fast(13, 17) == 221);
    assert(arithmos_lcmull_fast(4, 12) == 12);
    assert(arithmos_lcmull_fast(12, 4) == 12);
    assert(arithmos_lcmull_fast(6, 8) == 24);
    assert(arithmos_lcmull_fast(100, 80) == 400);
    assert(arithmos_lcmull_fast(ULLONG_MAX, 1) == ULLONG_MAX);

    overflow = arithmos_lcmull_fast_safe(0, 0, &res_ull);
    assert(res_ull == 0 && overflow == false);
    overflow = arithmos_lcmull_fast_safe(0, 5, &res_ull);
    assert(res_ull == 0 && overflow == false);
    overflow = arithmos_lcmull_fast_safe(10, 20, &res_ull);
    assert(res_ull == 20 && overflow == false);
    overflow = arithmos_lcmull_fast_safe(6, 8, &res_ull);
    assert(overflow == false && res_ull == 24);
    overflow = arithmos_lcmull_fast_safe(100, 80, &res_ull);
    assert(overflow == false && res_ull == 400);
    overflow = arithmos_lcmull_fast_safe(half_ull_max, 4, &res_ull);
    assert(overflow == true);
    overflow = arithmos_lcmull_fast_safe(1LL << 33, (1LL << 33) + 1, &res_ull);
    assert(overflow == true && res_ull == 8589934592);

    return 0;
}
