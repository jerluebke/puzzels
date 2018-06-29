#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#ifndef FILENAME
#define FILENAME "triangle"
#endif

#ifndef NUMBER_SIZE
#define NUMBER_SIZE 2
#endif

/****************************
 * Declarations
 ****************************/

typedef struct node node;

struct node {
    uint32_t val;   /* value in triangle */
    int64_t sum;    /* largest sum up to this node - init with -1 */
    char dir;       /* direction for largest sum */
    node *right;    /* right child */
    node *left;     /* left child */
};

void node_init(node *, uint32_t);

uint64_t node_get_sum(node *);

void make_triangle(node *, uint32_t *, size_t);


/****************************
 * Implementations
 ****************************/

void node_init(node *new, uint32_t val)
{
    new->val = val;
    new->sum = -1;
    new->dir = '\0';
}

uint64_t node_get_sum(node *self)
{
    /* last element - no children - return own value */
    if ((self->right == NULL) && (self->left == NULL))
        return self->val;
    /* sum was already calculated - return it */
    if (self->sum != -1)
        return self->sum;
    /* get sums from children */
    uint64_t right_sum = 0, left_sum = 0;
    if (self->right)
        right_sum = self->val + node_get_sum(self->right);
    if (self->left)
        left_sum = self->val + node_get_sum(self->left);
    /* set dir and sum to largest result and return it */
    self->dir = (right_sum > left_sum) ? 'r' : 'l';
    self->sum = (right_sum > left_sum) ? right_sum : left_sum;
    return self->sum;
}

void make_triangle(node *first, uint32_t *data, size_t lines)
{
    node *parent = first, *child = first + 1, *next_line;
    /* init first element */
    node_init(parent, *data++);
    for (size_t cur=1; cur<=lines; ++cur) {
        /* set first element of next row as end */
        next_line = parent + cur;
        while (parent != next_line) {
            /* init child */
            node_init(child, *data++);
            parent->right = child++;
            /* after incrementing the child ptr, its element will be initiated
             * either in the next iteration or after exiting this while loop */
            parent->left = child;
            ++parent;
        }
        node_init(child, *data++);
        ++child;    /* move child to next row */
    }
}


int main()
{
    FILE *fp;
    /* open file and check for errors */
    if (fopen_s(&fp, FILENAME, "r")) {
        fprintf(stderr, "Failed to open file \"%s\"...\n", FILENAME);
        return EXIT_FAILURE;
    }

    char c;
    /* start with 1 to include the last element while counting, which is not
     * followed by ' ' or '\n' (but by EOF) */
    size_t size = 1, lines = 1;
    /* count numbers and lines */
    while ((c = fgetc(fp)) != EOF)
        if (c == ' ')
            ++size;
        else if (c == '\n')
            ++size, ++lines;
    /* reset file to start */
    rewind(fp);

    /* allocate memory */
    uint32_t *data = malloc(size * sizeof(uint32_t));
    node *triangle = malloc(size * sizeof(node));

    /* write content from file in data */
    char buf[NUMBER_SIZE+1];
    int i = 0;
    while ((c = fgetc(fp)) != EOF)
        if (c == ' ' || c == '\n') {
            i = 0;
            *data = atoi(buf);
            ++data;
        } else {
            buf[i] = c;
            ++i;
        }
    fclose(fp);

    /* build triangle */
    make_triangle(triangle, data, lines);

    /* calculate and print largest sum */
    uint64_t sum = node_get_sum(triangle);
    printf("Largst sum: %llu", sum);

    /* don't forget! */
    free(data);
    free(triangle);

    return EXIT_SUCCESS;
}
