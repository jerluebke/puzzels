#include <stdlib.h>
#include <stdint.h>
#include <string.h>
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

inline static void node_init(node *, uint32_t);

uint64_t node_get_sum(node *);

void make_triangle(node *, size_t);


/****************************
 * Implementations
 ****************************/

inline static void node_init(node *new, uint32_t val)
{
    new->val    = val;
    new->sum    = -1;
    new->dir    = '\0';
    new->right  = NULL;
    new->left   = NULL;
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

void make_triangle(node *first, size_t lines)
{
    /* nodes have already been initiated in main
     * here: set relations */
    node *parent = first, *child = first + 1, *next_line;

    /* iterate from {1, ..., lines-1} since the last rows elements don't have
     * any children */
    for (size_t cur=1; cur<lines; ++cur) {
        /* set first element of next row as end */
        next_line = parent + cur;
        while (parent != next_line) {
            parent->right = child++;
            /* this parents left child is next iterations right child */
            parent->left = child;
            ++parent;
        }
        ++child;    /* move child to next row */
    }
}

void print_path(node *head)
{
    printf("path: ");
    while (head != NULL) {
        printf("%u ", head->val);
        switch (head->dir) {
            case 'r': head = head->right; break;
            case 'l': head = head->left; break;
            default: head = NULL;
        }
    }
    printf("\n");
}


int main(int argc, char **argv)
{
    /* open file and check for errors */
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file \"%s\"...\n", FILENAME);
        return EXIT_FAILURE;
    }

    char c;
    size_t size = 0, lines = 0;
    /* count numbers and lines */
    while ((c = fgetc(fp)) != EOF)
        if (c == ' ')
            ++size;
        else if (c == '\n')
            ++size, ++lines;

    printf("%zu numbers in %zu lines\n\n", size, lines);

    /* reset file to start */
    rewind(fp);

    /* allocate nodes in continuous memory */
    node *head = malloc(size * sizeof(node));
    if (head == NULL) {
        fprintf(stderr, "malloc failed... \n");
        return EXIT_FAILURE;
    }
    node *triangle = head;

    /* write content from file in notes */
    char buf[NUMBER_SIZE+1];
    int i = 0;
    while ((c = fgetc(fp)) != EOF)
        if (c == ' ' || c == '\n') {
            i = 0;
            node_init(triangle, atoi(buf));
            ++triangle;
        } else {
            buf[i] = c;
            ++i;
        }
    fclose(fp);

    make_triangle(head, lines);

    uint64_t sum = node_get_sum(head);
    printf("Largst sum: %lu\n", sum);

    if (argc > 1 && strcmp(argv[1], "path") == 0)
        print_path(head);

    /* don't forget! */
    free(head);

    return EXIT_SUCCESS;
}
