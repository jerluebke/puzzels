#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/* find largest prime factor 
 * interestingly without checking primality
 * credit to some guy on projecteuler.net */
uint64_t doit_2(uint64_t n)
{
    uint64_t div = 2;
    while (n > 1) {
        if ((n % div) == 0) {
            n /= div;
            --div;
        }
        ++div;
    }
    return div;
}


int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("This Programm takes one argument as input...\n");
        return -1;
    }

    char *endptr;
    uint64_t input = strtoul(argv[1], &endptr, 10);

    printf("Greatest prime factor of %llu = %llu\n", input, doit_2(input));
    return 0;
}
