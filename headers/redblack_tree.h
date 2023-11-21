#ifndef _REDBLACK_TREE_H_
#define _REDBLACK_TREE_H_
#include <stdbool.h>

typedef char *Key; // the key is a word

#define RED true
#define BLACK false

typedef struct node RBT;
typedef int Value; // the value is a documents to be added to the array

typedef struct
{
    int *doc_array;
    int max_size;
    int n_docs;
} doc_array;

struct node
{
    Key key;
    doc_array val;
    bool color;
    RBT *l, *r;
};

doc_array *search(RBT *n, Key key);
RBT *RBT_insert(RBT *h, Key key, Value val);
RBT *RBT_contruct();
void print_value(doc_array val);
void freeTree(RBT *root);

#endif