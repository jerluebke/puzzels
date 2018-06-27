#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../isprime.h"

/* *
 * find the first `len` prime numbers
 * writing the result into the provided buffer `res`
 * and returning a pointer to its first element
 * */
uint64_t *find_primes(uint64_t *res, size_t len)
{
    /* start will be returned (pointing to the first adress of res)
     * end is the first address after the allocated memory */
    uint64_t *start = res, *end = res + len;

    /* set first two primes and start with 5 */
    *res++ = 2;
    *res++ = 3;
    uint64_t cand = 5;
    /* check every 6*k±1 number (k ∈ {0, 1, ...})
     * the remaining ones are multiples of 2 or 3 */
    while (res != end) {
        if (isprime(cand))
            *res++ = cand;
        /* another bound check to not write past allocated memory after
         * incrementing the pointer before */
        if (isprime(cand+2) && res != end)
            *res++ = cand+2;
        cand += 6;
    }
    return start;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        puts("program takes one argument...");
        return EXIT_FAILURE;
    }
    char *buf;
    size_t len = strtol(argv[1], &buf, 10);

    /* allocate memory to store primes in */
    uint64_t *start = (uint64_t *)malloc(len * sizeof(uint64_t));
    if (start == NULL) {
        fprintf(stderr, "malloc failed...\n");
        return EXIT_FAILURE;
    }

    uint64_t *end = start + len;
    uint64_t *primes = find_primes(start, len);
    if (argc > 2 && strcmp("all", argv[2]) == 0) {
        while (primes != end)
            printf("%llu\n", *primes++);
    }
    else if (argc > 2 && strcmp("bin", argv[2]) == 0) {
        FILE *fb = fopen("primes.bin", "wb");
        fwrite(primes, sizeof *primes, len, fb);
        fclose(fb);
    }
    else {
        printf("%llu\n", *(primes+=(len-1)));
    }
    
    free(start);
    return EXIT_SUCCESS;
}
