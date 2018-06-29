#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint64_t binomial(uint64_t n, uint32_t k)
{
    double res = 1, div = 1;
    uint32_t i;
    for (i=1; i<=k; ++i) {
        res *= (n + 1 - i);
        div *= i;
    }
    return res / div;
}
/* number of paths is binomial(2*n, n) = (2*n)! / (n!*n!)
 * one has to go n steps right and n steps down (i.e. 2*n in total) yielding
 * (2*n)! possibilities to put steps, divided by (n!)^2 since the the steps are
 * not unique
 */
int main(int argc, char **argv)
{
    if (argc < 2) {
        fputs("this programm takes one argument...", stderr);
        return EXIT_FAILURE;
    }
    char *buf;
    uint64_t gs = strtol(argv[1], &buf, 10);    /* grid size */
    printf("Possibilities for a %llux%llu grid: %llu\n", gs, gs, binomial(2*gs, gs));
    return EXIT_SUCCESS;
}
