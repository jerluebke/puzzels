#include <stdio.h>
#include <stdlib.h>
#include "itoa.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        puts("program takes one argument...");
        return -1;
    }

    char *end;
    uint64_t input = strtol(argv[1], &end, 10);
    int len = snprintf(NULL, 0, "%lu", input);
    char *res = (char *)malloc(len+1);

    printf("itoa(%lu) = \"%s\"\n", input, my_itoa(input, res, 10));
    free(res);

    return 0;
}
