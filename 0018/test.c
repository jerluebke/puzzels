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
    init(&n, 1);
    printf("n = {i=%d}\n", n.i);
    init(&n, 456);
    printf("n = {i=%d}\n", n.i);
    return 0;
}
