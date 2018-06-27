#include <stdio.h>
#include <stdlib.h>

#define LENGTH 13

typedef struct {
    int *start;
    int *end;
    unsigned long long prod;
} result;


/* find largest product
 * same as sol_1 but with an additional while loop instead of gotos*/
result flp(int *first, int *last)
{
    int *start = first, *end = first, *tmp;
    result res = { .prod = 1 };
    unsigned long long prod;
    while (end != last) {
        do {
            ++end;
        } while (*end != 0);
        while ((end-start) >= LENGTH) {
            prod = 1;
            for (tmp = start; tmp != start+LENGTH; ++tmp)
                prod *= *tmp;
            if (prod > res.prod) {
                res.prod = prod;
                res.start = start;
                res.end = tmp;
            }
            ++start;
        }
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
