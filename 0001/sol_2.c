#include <stdio.h>

#ifndef LIMIT
#define LIMIT 10000000
#endif

long doit2()
{
    long cnt = 0;
    int t, f;
    for (t=0; t<LIMIT; t+=3)
        cnt += t;
    for (f=0; f<LIMIT; f+=5) {
        if (f%3 == 0)
            continue;
        cnt += f;
    }
    return cnt;
}

int main()
{
    long cnt = doit2();
    printf("%ld", cnt);
}
