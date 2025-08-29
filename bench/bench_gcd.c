#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#define NUM_ITERATIONS 10000000


static unsigned long long ar_gcdu(unsigned long long a, unsigned long long b) {
    while (b) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }

    static int c = 5000;

    return a;
}

int main() {
    return ar_gcdu(15, 3);
}
