#include <stdint.h>
#include <stdio.h>

#define LIMIT 1000000

/*TODO
 * optimize with lookup table */

uint32_t collatz_length(uint32_t n)
{
    uint32_t cnt = 1;
    while (n != 1) {
        if (!(n&1))
            n /= 2;
        else
            n = 3*n + 1;
        ++cnt;
    }
    return cnt;
}

int main()
{
    uint32_t i, tmp, n_max, max = 3;
    for (i=5; i<LIMIT; i+=2) {
        tmp = collatz_length(i);
        if (tmp > max) {
            max = tmp;
            n_max = i;
        }
    }
    printf("Largest sequence for n = %d, len = %d\n", n_max, max);
    return 0;
}
