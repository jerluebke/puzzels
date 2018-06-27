#ifndef ISPRIME_H
#define ISPRIME_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/*
 * TODO
 *  this implementation seems to give a wrong result for large samples, e.g.
 *      67280421310721 = (2^64+1)/274177 (largest prime by 1855)
 *      4398042316799   11th Carol prime
 *      274876858367    10th Carol prime
 *      87178291199     10th Factorial prime
 *      99194853094755497   12th Fibonacci prime
 *      19577194573     27th Markov prime
 *      2305843009213693951 9th Mersenne prime
 *  are supposed to be prime, but return false.
 *  This might require further investigation...
 * */

/* Limits and bases to check for mrt being deterministic
 * source:
 * en.wikipedia.org/wiki/Miller-Rabin_primality_test#Deterministic_variants */
#define MAX_LIMIT 318665857834031151167461 /* too large for long long int */
#define A_LIMIT 3825123056546413051
#define B_LIMIT 341550071728321
#define C_LIMIT 3474749660383
#define D_LIMIT 2152302898747
#define E_LIMIT 4759123141
#define F_LIMIT 9080191
#define G_LIMIT 1373653

#define MAX max[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}
#define A a[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23}
#define B b[7] = {2, 3, 5, 7, 11, 13, 17}
#define C c[6] = {2, 3, 5, 7, 11, 13}
#define D d[5] = {2, 3, 5, 7, 11}
#define E e[3] = {2, 7, 61}
#define F f[2] = {31, 73}
#define G g[2] = {2, 3}

#define SIZEOFARR(x) (sizeof(x) / sizeof(x[0]))

/*
 * Miller-Rabin-Test
 *
 * input: long long int n (to check if prime), int a (base)
 * return true if n is propably prime
 *
 * find d (odd) and j, such that
 *  n-1 == d*2^j
 *
 * check
 *  (a^d) % n == 1 % n          (I)
 * or
 *  (a^(d*2^r)) % n == -1 % n   (II)
 *
 * if these hold true for n, then n is propably prime
 *
 * */
bool mrt(uint64_t n, uint64_t a)
{
    uint64_t d = (n-1) >> 1;    /* d = floor((n-1)/2) */
    int j = 1;
    while ((d & 1) == 0) {      /* while d is even (d % m == d & (m-1)) */
        d >>= 1;                /* divide d by 2 and increment j (exponent) */
        ++j;
    }                           /* now: d is odd and (n-1) == d*2^j */

    /* the following loop calculates the `modular exponentiation`,
     * that is (a^d) % n
     * mathematically: (a mod n)*(b mod n) == (a*b) mod n */
    uint64_t res = a;
    while (d >>= 1) {           /* d = d/2 and check if d != 0 */
        a = (a*a) % n;
        if (d & 1)              /* if d is odd multiply base with result */
            res = (res*a) % n;
    }
    if (res == 1 || res == (n-1))   /* (I) or (II) holds true */
        return true;                /* n is propably true */

    /* if above test didn't yield a result, check (res^j) % n == n-1 */
    for (int k=1; k<j; ++k) {
        res = (res*res) % n;
        if (res == (n-1))
            return true;
        if (res <= 1)
            break;
    }

    return false;   /*if all of the above failed, n is definitly not prime */
}


/* prepare input for Miller-Rabin-Test and check for all relevant a */
bool isprime(uint64_t n)
{
    int size = 0;
    int *base = NULL;

    if (n == 2) {
        return true;
    } else if (n < 2 || !(n & 1)) {  /* check if n is even */
        return false;
    } else if (n >= A_LIMIT) {
        fprintf(stderr, "input too large!\ninput = %lu\nLIMIT = %ld", n, A_LIMIT);
        return false;
    } else if (n < G_LIMIT) {
        int G;
        size = SIZEOFARR(g);
        base = &g[0];
    } else if (n < F_LIMIT) {
        int F;
        size = SIZEOFARR(f);
        base = &f[0];
    } else if (n < E_LIMIT) {
        int E;
        size = SIZEOFARR(e);
        base = &e[0];
    } else if (n < D_LIMIT) {
        int D;
        size = SIZEOFARR(d);
        base = &d[0];
    } else if (n < C_LIMIT) {
        int C;
        size = SIZEOFARR(c);
        base = &c[0];
    } else if (n < B_LIMIT) {
        int B;
        size = SIZEOFARR(b);
        base = &b[0];
    } else if (n < A_LIMIT) {
        int A;
        size = SIZEOFARR(a);
        base = &a[0];
    }

    int *endptr = base + size;
    for (; base!=endptr; ++base) {
        if (!mrt(n, *base))
            return false;
    }

    return true;
}

#endif  /* end include guard */
