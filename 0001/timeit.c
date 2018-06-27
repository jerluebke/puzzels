#include <stdio.h>
#include <time.h>
/* include what to time */
#define main foo1
#include "sol_1.c"
#undef main
#define main foo2
#include "sol_3.c"
#undef main

int main()
{
    clock_t start1, total1, start2, total2;
    long res;

    start1 = clock();
    res = doit1();
    total1 = clock() - start1;

    start2 = clock();
    res = doit3();
    total2 = clock() - start2;

    printf("In CPU ticks:\n");
    printf("\tprocess 1: %ld\n\tprocess 2: %ld\n", total1, total2);
    printf("In seconds:\n");
    printf("\tprocess 1: %f\n\tprocess 2: %f\n",
            (double)total1/CLOCKS_PER_SEC, (double)total2/CLOCKS_PER_SEC);
}
