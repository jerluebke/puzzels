#include <stdio.h>

#ifndef LIMIT
#define LIMIT 10000000
#endif

long doit3()
{
    long cnt = 0;
    int t, f, ft;
    for (t=f=ft=0; t<LIMIT; t+=3) {
        cnt+=t;
        if (f < LIMIT) {
            cnt+=f;
            f+=5;
        }
        if (ft < LIMIT) {
            cnt-=ft;
            ft+=15;
        }
    }
    return cnt;
}

int main()
{
    long cnt = doit3();
    printf("%ld", cnt);
}
