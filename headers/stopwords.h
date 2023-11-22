#ifndef _STOPWORD_H_
#define _STOPWORD_H_
#include <stdbool.h>

typedef char* Key;

#define RED true
#define BLACK false

struct sw_node
{
    Key key;
    bool color;
    struct sw_node *l, *r;
};

typedef struct sw_node swTree;

swTree *swTree_construct();
swTree *swTree_insert(swTree *swt, Key word);
bool search_sw(swTree *t, Key key);
void free_swTree(swTree *s);

#endif