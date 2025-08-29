#include <assert.h>
#include <limits.h>

#include "arithmos/number-theory/gcd.h"
#include "arithmos/number-theory/int128.h"

int main() {
    assert(arithmos_gcdll(0, 0) == 0);
    assert(arithmos_gcdll(0, 123456) == 123456);
    assert(arithmos_gcdll(78910, 0) == 78910);
    assert(arithmos_gcdll(42, 42) == 42);
    assert(arithmos_gcdll(35, 64) == 1);
    assert(arithmos_gcdll(21, 7) == 7);
    assert(arithmos_gcdll(-48, 18) == 6);
    assert(arithmos_gcdll(48, -18) == 6);
    assert(arithmos_gcdll(-48, -18) == 6);
    assert(arithmos_gcdll(LLONG_MAX, 1) == 1);
    assert(arithmos_gcdll(LLONG_MAX, LLONG_MIN) == 1);

    assert(arithmos_gcdull(0, 0) == 0);
    assert(arithmos_gcdull(0, 123456) == 123456);
    assert(arithmos_gcdull(78910, 0) == 78910);
    assert(arithmos_gcdull(42, 42) == 42);
    assert(arithmos_gcdull(35, 64) == 1);
    assert(arithmos_gcdull(21, 7) == 7);
    assert(arithmos_gcdull(ULLONG_MAX, 1) == 1);
    assert(arithmos_gcdull(1ULL << 63, 1ULL << 62) == 1ULL << 62);
    assert(arithmos_gcdull(982451653, 57885161) == 1);

    assert(arithmos_gcd128(0, 0) == 0);
    assert(arithmos_gcd128(0, 123456) == 123456);
    assert(arithmos_gcd128(78910, 0) == 78910);
    assert(arithmos_gcd128(42, 42) == 42);
    assert(arithmos_gcd128(35, 64) == 1);
    assert(arithmos_gcd128(21, 7) == 7);
    assert(arithmos_gcd128(-48, 18) == 6);
    assert(arithmos_gcd128(48, -18) == 6);
    assert(arithmos_gcd128(-48, -18) == 6);
    assert(arithmos_gcd128(INT128_MAX, 1) == 1);
    assert(arithmos_gcd128(INT128_MAX, INT128_MIN) == 1);

    assert(arithmos_gcdu128(0, 0) == 0);
    assert(arithmos_gcdu128(0, 123456) == 123456);
    assert(arithmos_gcdu128(78910, 0) == 78910);
    assert(arithmos_gcdu128(42, 42) == 42);
    assert(arithmos_gcdu128(35, 64) == 1);
    assert(arithmos_gcdu128(21, 7) == 7);
    assert(arithmos_gcdu128(UINT128_MAX, 1) == 1);
    assert(arithmos_gcdu128((__uint128_t)1 << 63, (__uint128_t)1 << 62) == (__uint128_t)1 << 62);
    assert(arithmos_gcdu128(982451653, 57885161) == 1);

    assert(arithmos_gcdll_fast(0, 0) == 0);
    assert(arithmos_gcdll_fast(0, 123456) == 123456);
    assert(arithmos_gcdll_fast(78910, 0) == 78910);
    assert(arithmos_gcdll_fast(42, 42) == 42);
    assert(arithmos_gcdll_fast(35, 64) == 1);
    assert(arithmos_gcdll_fast(21, 7) == 7);
    assert(arithmos_gcdll_fast(-48, 18) == 6);
    assert(arithmos_gcdll_fast(48, -18) == 6);
    assert(arithmos_gcdll_fast(-48, -18) == 6);
    assert(arithmos_gcdll_fast(LLONG_MAX, 1) == 1);
    assert(arithmos_gcdll_fast(LLONG_MAX, LLONG_MIN) == 1);

    assert(arithmos_gcdull_fast(0, 0) == 0);
    assert(arithmos_gcdull_fast(0, 123456) == 123456);
    assert(arithmos_gcdull_fast(78910, 0) == 78910);
    assert(arithmos_gcdull_fast(42, 42) == 42);
    assert(arithmos_gcdull_fast(35, 64) == 1);
    assert(arithmos_gcdull_fast(21, 7) == 7);
    assert(arithmos_gcdull_fast(ULLONG_MAX, 1) == 1);
    assert(arithmos_gcdull_fast(1ULL << 63, 1ULL << 62) == 1ULL << 62);
    assert(arithmos_gcdull_fast(982451653, 57885161) == 1);

    return 0;
}
