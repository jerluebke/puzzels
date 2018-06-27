#include <stdio.h>

#ifndef LIMIT
#define LIMIT 4E6
#endif

/* sum of even fibonacci numbers */
long doit_2()
{
    long sum, a, b;
    sum = 0;
    a = 1; b = 2;
    while (b < LIMIT) {
        sum += (a + b);
        a = a + 2*b;
        b = 2*a + 3*b;
    }
    return sum;
}

int main()
{
    printf("%ld\n", doit_2());
}
