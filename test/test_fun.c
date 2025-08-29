#include <stdio.h>
#include <stdlib.h>

#include <arithmos/arithmos.h>



void arithmos_bigint_pow2(Arithmos_BigInt* result, size_t exponent) {
    Arithmos_BigInt temp;
    arithmos_bigint_init(&temp);

    arithmos_bigint_from_u64(result, 1, false);

    for (size_t i = 0; i < exponent; ++i) {
        // temp = result
        arithmos_bigint_copy(&temp, result);

        // result = result + result
        arithmos_bigint_sum(&temp, &temp, result);
    }

    arithmos_bigint_destroy(&temp);
}

int main() {
    Arithmos_BigInt temp, one, result;
    arithmos_bigint_init(&temp);
    arithmos_bigint_init(&one);
    arithmos_bigint_init(&result);
    arithmos_bigint_from_u64(&one, 1, false);

    arithmos_bigint_pow2(&temp, 1000000);
    arithmos_bigint_difference(&temp, &one, &result);

    char* s = arithmos_bigint_to_string(&result);
    printf("%s\n", s);
    free(s);

    arithmos_bigint_destroy(&temp);
    arithmos_bigint_destroy(&one);
    arithmos_bigint_destroy(&result);

    return 0;
}
