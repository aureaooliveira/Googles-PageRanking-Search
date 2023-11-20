#ifndef _REDBLACK_TREE_H_
#define _REDBLACK_TREE_H_
#include <stdbool.h>

typedef char *Key; // the key is a word
typedef int Value; // the value is a list of documents

#define RED true
#define BLACK false

typedef struct node RBT;
struct node
{
    Key key;
    Value val;
    bool color;
    RBT *l, *r;
};

Value search(RBT *n, Key key);
RBT *RBT_insert(RBT *h, Key key, Value val);
RBT *RBT_contruct();

#endif