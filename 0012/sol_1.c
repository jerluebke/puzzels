#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE    1500    /* number of primes read from file */
#define LIMIT   500
#define LOWER   1200    /* initial guess:
                           tri(1200) = 720600 as lower bound for
                           720720, with d = 240 
                           (see wikipedia: Highly composite number)*/

/* number of divisors
 * d(n) = (c1+1)*(c2+1)*...*(ck+1) 
 * where n = p1^c1 * p2^c2 *...* pk^ck */
uint32_t d(uint64_t n, uint64_t *primes)
{
    uint32_t exp;
    uint32_t i = 0, d = 1;
    /* prime factorization and counting exponents */
    while (n != 1) {
        exp = 0;
        while ((n % primes[i]) == 0) {
            ++exp;
            n /= primes[i];
        }
        d *= (exp + 1);
        ++i;
        if (i == SIZE) {
            fprintf(stderr, "Not enough primes!\n");
            exit(-1);
        }
    }
    return d;
}

int main()
{
    uint64_t primes[SIZE];
    FILE *fb = fopen("../primes.bin", "rb");
    size_t ret_code = fread(primes, sizeof *primes, SIZE, fb);
    if (ret_code != SIZE) {
        perror("Error reading primes.bin");
        return EXIT_FAILURE;
    }
    fclose(fb);

    uint32_t nd;    /* number of divisors */
    uint64_t tri;   /* triangle number */
    for (uint32_t i=LOWER;; ++i) {
        tri = (i*i + i)/2;  /* sum from 1 to i */
        if (tri < 0) {
            fprintf(stderr, "Integer Overflow, nothing found...\n");
            return EXIT_FAILURE;
        }
        nd = d(tri, primes);
        /* printf("tri(%u)=%lu, d(%lu)=%u\n", i, tri, tri, nd); */
        if (nd >= LIMIT) {
            printf("tri(%u) = %lu, d = %u\n", i, tri, nd);
            break;
        }
    }
    return 0;
}
