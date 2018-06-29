#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define NUM_LENGTH  50
#define NUMBERS     100
#define TO_CONSIDER 11

/* print first ten digits of sum of given numbers */
int main()
{
    /* continuous 2d-array, see:
     *  https://stackoverflow.com/a/39816048/9133910
     *  https://stackoverflow.com/a/36890904/9133910 */
    int (*numbers)[NUMBERS] = malloc(NUM_LENGTH * sizeof *numbers);
    int i = 0, j = 0;
    char c;
    while ((c = getchar()) != EOF && j < NUMBERS)
        if (c == '\n')
            i = 0, ++j;
        else
            numbers[i][j] = c-'0', ++i;

    long long fd;
    long long sum = 0;

    for (j=0; j<NUMBERS; ++j) {
        /* printf("%d\n", numbers[0][j]); */
        for (i=0, fd=0; i<TO_CONSIDER; ++i)
            fd += numbers[i][j]*pow(10, TO_CONSIDER-1-i);
        sum += fd;
    }
    printf("first digits of sum: %lld\n", sum);
        
    free(numbers);
    return 0;
}
