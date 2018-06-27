#include "../isprime.h"

/* *
 * find the sum of the prime numbers below n
 * */
uint64_t sum_primes(uint64_t n)
{
    uint64_t sum = 5;   /* 2 + 3 */
    uint64_t cand = 5;
    /* check every 6*k±1 number (k ∈ {0, 1, ...})
     * the remaining ones are multiples of 2 or 3 */
    while (cand < n) {
        if (isprime(cand))
            sum += cand;
        if (isprime(cand+2) && (cand+2) < n)
            sum += cand+2;
        cand += 6;
    }
    return sum;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        puts("program takes one argument...");
        return EXIT_FAILURE;
    }

    char *end;
    uint32_t n = strtol(argv[1], &end, 10);
    printf("sum of first %u primes: %lu\n", n, sum_primes(n));

    return EXIT_SUCCESS;
}
