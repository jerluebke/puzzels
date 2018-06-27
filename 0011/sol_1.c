#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define X_LEN           20
#define TOTAL_LEN       400
#define NUMBER_LENGTH   2
#define PROD_LEN        4

typedef struct {
    uint64_t prod;
    short *start;
    short ns[PROD_LEN];
    char dir;
} result;


/* find greatest product in grid going in all directions */
result fgp_all_directions(short *start, short *end)
{
    /* start of current sequence, end of line, current position*/
    short *st = start, *eol = start + X_LEN, *cur;
    /* position at 4 steps right, down, diagonally up and down */
    short *rt, *dw, *dg_up, *dg_dw;
    /* count variable for loops */
    short i;
    /* structs holding data for current loop and greatest result seen */
    result res_tmp, res, res_max = {.prod=1};

    while (st != end) {
        res.prod = 1;       /* needed for comparisons */
        res_tmp.start = st; /* current starting position
                                will be copied into final result */

        /* when calculating the product, include the value of the
         * end-pointer of the sequence (to make bound checking easier)*/
        /* looking downwards */
        dw = st + (PROD_LEN-1) * X_LEN;
        if (dw < end) {
            res_tmp.prod = 1;
            res_tmp.dir = 'v';  /* vertically down */
            for (i=0, cur=st; cur<=dw; ++i) {
                res_tmp.ns[i] = *cur;   /* record sequence */
                res_tmp.prod *= *cur;   /* compute product */
                cur += X_LEN;   /* move pointer down one row */
            }
            if (res_tmp.prod > res.prod)
                res = res_tmp;  /* copy data */
        }

        /* looking right */
        rt = st + PROD_LEN-1;
        if (rt == eol) {
            /* no sequence long enough can be found anymore looking
             * right or diagonally -> next line */
            st = eol;
            eol += X_LEN;
            continue;
        }
        res_tmp.prod = 1;
        res_tmp.dir = 'r';
        for (i=0, cur=st; cur<=rt; ++i, ++cur) {
            res_tmp.ns[i] = *cur;
            res_tmp.prod *= *cur;
        }
        if (res_tmp.prod > res.prod)
            res = res_tmp;

        /* looking diagonally up right */
        dg_up = st + PROD_LEN-1 - (PROD_LEN-1) * X_LEN;
        if (dg_up > start) {
            res_tmp.prod = 1;
            res_tmp.dir = 'u';
            for (i=0, cur=st; cur>=dg_up; ++i) {
                res_tmp.ns[i] = *cur;
                res_tmp.prod *= *cur;
                cur -= (X_LEN - 1); /* move ptr up and right */
            }
            if (res_tmp.prod > res.prod)
                res = res_tmp;
        }

        /* looking diagonally down right */
        dg_dw = st + PROD_LEN-1 + (PROD_LEN-1) * X_LEN;
        if (dg_dw < end) {
            res_tmp.prod = 1;
            res_tmp.dir = 'd';
            for (i=0, cur=st; cur<=dg_dw; ++i) {
                res_tmp.ns[i] = *cur;
                res_tmp.prod *= *cur;
                cur += (X_LEN + 1); /* move ptr down and right */
            }
            if (res_tmp.prod > res.prod)
                res = res_tmp;
        }

        /* check if largest until now and save */
        if (res.prod > res_max.prod)
            res_max = res;

        ++st;   /* increment starting position */
    } /* end outer while */

    return res_max;
}


int main()
{
    /* allocate memory */
    short *start = (short *)malloc(TOTAL_LEN * sizeof(short));
    if (start == NULL) {
        fprintf(stderr, "malloc failed...\n");
        return EXIT_FAILURE;
    }
    short *buf = start, *end = start + TOTAL_LEN;

    /* temp storage for numbers */
    char c[NUMBER_LENGTH+1];
    int i = 0;
    while ((c[i] = getchar()) != EOF) {
        if (c[i] == '\n' || c[i] == ' ')
            goto write;
        else if (i < NUMBER_LENGTH)
            ++i;    /* next digit */
        else
            goto write;
        continue;
write:  /* all digits were read, save as number and continue */
        i = 0;
        *buf = atoi(c);
        ++buf;
    }

    result res = fgp_all_directions(start, end);
    char *dir;
    switch (res.dir) {
        case 'r':
            dir = "right";
            break;
        case 'v':
            dir = "down";
            break;
        case 'u':
            dir = "diag up";
            break;
        case 'd':
            dir = "diag down";
            break;
    }
    short x = (res.start-start) % X_LEN;
    short y = (res.start-start) / X_LEN;

    printf("Largest Product = %lu\nat (%d, %d) going %s\n",
            res.prod, x, y, dir);
    printf("sequence: ");
    for (int i=0; i<4; ++i)
        printf("%d ", res.ns[i]);
    printf("\n");

    free(start);
    return EXIT_SUCCESS;
}
