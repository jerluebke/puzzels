#include <stdio.h>
#include <stdlib.h>

#define LENGTH 13

typedef struct {
    int *start;
    int *end;
    unsigned long long prod;
} result;


/* find largest product */
result flp(int *first, int *last)
{
    int *start = first, *end = first, *tmp;
    result res = { .prod = 1 };
    unsigned long long prod;

    while (end != last) {
        do {
            ++end;          /* find next 0 and put end there */
        } while (*end != 0);

        if ((end-start) < LENGTH)
            goto next_iter; /* increment end and continue */

next_slice: /* find largest product in array slice */
        prod = 1;
        for (tmp = start; tmp != start+LENGTH; ++tmp)
            prod *= *tmp;   /* make product */
        if (prod > res.prod) {
            res.prod = prod;
            res.start = start;
            res.end = tmp;  /* tmp is last position to be considered */
        }
        ++start;
        if ((end-start) > LENGTH) { /* there is still some left */
            ++start;         /* I'm not exactly sure, why start needs to be */
            goto next_slice; /* incremented again, but otherwise it gives a */
        }                    /* wrong result... */

next_iter:  /* common routine before continuing loop */
        ++end;
        start = end;
    }
    return res;
}


int main(int argc, char **argv)
{
    size_t buf_size = 1000;     /* default value */
    if (argc > 1) {
        char *tmp;
        buf_size = strtol(argv[1], &tmp, 10);
    }

    int *start = (int *)malloc(sizeof(int) * (buf_size+1)); /* allocate buffer */
    int *buf = start, *end = start + buf_size;
    int c;
    while ((c = getchar()) != EOF)      /* read from stdin char-wise and write */
        if (c == '\n')                  /* into buffer if current char is not  */
            continue;                   /* newline */
        else if (buf != end)
            *buf++ = c-'0';             /* convert char to int */
        else
            break;

    result res = flp(start, end);
    printf("Sequence starting at %ld:\n", res.start-start);
    for (buf = res.start; buf != res.end; ++buf)
        printf("%d", *buf);
    printf("\nproduct = %llu\n", res.prod);

    free(start);
    return 0;
}
