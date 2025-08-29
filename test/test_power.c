#include <assert.h>

#include "arithmos/number-theory/power.h"

int main() {
    assert(arithmos_power(2, 0) == 1);
    assert(arithmos_power(0, 0) == 1);
    assert(arithmos_power(0, 5) == 0);
    assert(arithmos_power(5, 1) == 5);
    assert(arithmos_power(1, 10000) == 1);
    assert(arithmos_power(2, 3) == 8);
    assert(arithmos_power(10, 5) == 100000);
    assert(arithmos_power(2, 63) == 9223372036854775808ULL);

    unsigned long long result;

    assert(arithmos_power_safe(2, 0, &result) == false && result == 1);
    assert(arithmos_power_safe(0, 0, &result) == false && result == 1);
    assert(arithmos_power_safe(0, 10, &result) == false && result == 0);
    assert(arithmos_power_safe(5, 1, &result) == false && result == 5);
    assert(arithmos_power_safe(3, 4, &result) == false && result == 81);
    assert(arithmos_power_safe(2, 64, &result) == true && result == 0);
    assert(arithmos_power_safe(2, 63, &result) == false && result == 9223372036854775808ULL);

    assert(arithmos_power_mod(2, 0, 5) == 1);
    assert(arithmos_power_mod(0, 0, 5) == 1);
    assert(arithmos_power_mod(0, 5, 7) == 0);
    assert(arithmos_power_mod(5, 1, 3) == 2);
    assert(arithmos_power_mod(10, 0, 1) == 0);
    assert(arithmos_power_mod(2, 10, 0) == 0);
    assert(arithmos_power_mod(3, 3, 5) == 2);
    assert(arithmos_power_mod(10, 5, 17) == 6);
    assert(arithmos_power_mod(2, 63, 1000) == 9223372036854775808ULL % 1000); // 2^63 % 1000 = 0 (actual value is 9223372036854775808 % 1000)
    assert(arithmos_power_mod(2, 63, 1009) == (unsigned long long)(9223372036854775808ULL % 1009));

    return 0;
}
