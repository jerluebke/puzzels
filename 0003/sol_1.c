#include <math.h>
#include "isprime.h"


/* find greatest prime factor */
uint64_t doit_1(uint64_t n)
{
    uint64_t p, f_max = 1, q = sqrt(n);
    for (; q>1; --q) {
        if ((n % q) == 0) {
            if (q > f_max && isprime(q))
                f_max = q;
            p = n / q;
            if (p > f_max && isprime(p))
                f_max = p;
        }
    }
    return f_max == 1 ? n : f_max;
}


int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("This Programm takes one argument as input...\n");
        return -1;
    }

    char *endptr;
    uint64_t input = strtoul(argv[1], &endptr, 10);

    printf("Greatest prime factor of %llu = %llu\n", input, doit_1(input));
    return 0;
}
