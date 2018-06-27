#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../isprime.h"
#include "../itoa.h"

#ifndef WITH_MATH
#define WITH_MATH 1
#endif

#define UPPER 999
#define LOWER 99

/* *
 * make palindrome   number with even number of digits
 * input: first half of digits of the desired number
 *  e.g. 123
 * returns palindrome number
 *  e.g. 123321
 * */
int make_pal_str(int half)
{
    int ipal;
    /* length of input (lower half of palindrome) */
    int len = snprintf(NULL, 0, "%d", half);
    /* buffer to write palindrome into */
    char *cpal = (char *)malloc(2*len+1);
    /* pointers pointing at floor(len/2) and ceil(len/2) */
    char *cpal1 = cpal + len -1, *cpal2 = cpal1 +1;
    cpal = my_itoa(half, cpal, 10);     /* int to str */
    /* write lower half reversly into upper half
     * stop before last element to aviod accessing unallocated memory */
    while (cpal1 > cpal) {
        *cpal2++ = *cpal1--;
    }
    *cpal2++ = *cpal1;  /* write last element */
    *cpal2 = '\0';      /* add NULL terminator */
    ipal = atoi(cpal);  /* str to int */
    free(cpal);
    return ipal;
}

/* *
 * make palindrome just like above, but calculating it from the given integers
 * (no converting to and from strings)
 * (this one seems to be slower, actually...)
 * */
int make_pal_math(int pal)
{
    int tmp = pal;
    /* number of digits of input, that is the lower half of the palindrome*/
    int len = floor(log10(pal)) + 1;
    /* move lower half up and add `len` zeros
     * e.g.: pal = 123 -> pal = 123000 */
    pal *= pow(10, len);
    int i, j, digit;
    int pow_i = pow(10, len-1), pow_j = 1;
    for (i=len-1, j=0; i>=0; --i, ++j) {
        digit = tmp / pow_i;    /* get current digit, i.e. first digit of tmp */
        tmp -= digit * pow_i;   /* decrement tmp for next iteration */
        pal += digit * pow_j;   /* add to palindrome at corresponding position */
        pow_i /= 10;    /* update powers for next iteration which indicate the digits positions */
        pow_j *= 10;
    }
    return pal;
}

/* *
 * find greatest palindromic number pal = p*q with p, q being 3-digit numbers
 * input: pointers to store the results for the palindrome and its factors at
 * returns 0 upon success and -1 if no match was found
 * */
int gfp(int *pal, int *p, int *q)
{
    for (int i=UPPER-2; i>LOWER; --i) {
#if WITH_MATH
        *pal = make_pal_math(i);
#else
        *pal = make_pal_str(i);
#endif
        if (isprime(i))  /* miller rabin prime test */
            continue;
        /* else */
        /* begin at √pal and go downwards while checking that p, q are still
         * within their bounds (being 3-digit numbers) */
        for (*p=sqrt(*pal), *q=*pal / *p; *p>LOWER && *q<UPPER; --(*p)) {
            *q = *pal / *p;
            /* the first match gives the largest factors */
            if ((*pal % *p) == 0)
                return 0;
        }
    } /* end outer for */
    return -1;
}


int main()
{
    int pal, p, q;
    gfp(&pal, &p, &q);
    printf("%d = %d * %d\n", pal, p, q);
    return 0;
}
