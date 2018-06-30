#include <stdio.h>

struct node {
    short i;
};

void init(struct node *n, short val)
{
    n->i = val;
}

int main()
{
    struct node n;
    printf("%llu, %llu\n", sizeof(struct node *), sizeof(int *));
    return 0;
}
