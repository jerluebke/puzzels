#include <stdio.h>
#include <math.h>

#ifndef LIMIT
#define LIMIT 4E6
#endif

/* nth fibonacci number */
long f_n(int n)
{
    return (long) pow((1+sqrt(5))/2, n) / sqrt(5) + 0.5;
}

/* sum of even fibonacci numbers */
long doit_1()
{
    long sum = 0;
    long f_i = 0;
    for (int i=3; f_i < LIMIT; f_i = f_n(i), i+=3)
        sum += f_i;
    return sum;
}

int main()
{
    printf("%ld\n", doit_1());
}
