#include <stdio.h>
#include <time.h>

#ifndef LIMIT
#define LIMIT 10000000
#endif

long doit1()
{
    long cnt = 0;
    for (int i=0; i<LIMIT; ++i) {
        if (i%3==0 || i%5==0)
            cnt+=i;
    }
    return cnt;
}

int main()
{
    long cnt = doit1();
    printf("%ld", cnt);
}
