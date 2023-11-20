#include "../../headers/redblack_tree.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define NULL_Value 0

RBT *RBT_contruct()
{
    RBT *node = NULL;
}

RBT *create_node(Key key, Value val, bool color)
{
    RBT *node = malloc(sizeof(RBT));
    node->key = key;
    node->val = val;
    node->color = RED;
    node->l = NULL;
    node->r = NULL;
    return node;
}

int compare(Key k1, Key k2)
{
    return strcmp(k1, k2);
}

Value search(RBT *n, Key key)
{
    while (n != NULL)
    {
        int cmp;
        cmp = compare(key, n->key);
        if (cmp < 0)
            n = n->l;
        else if (cmp > 0)
            n = n->r;
        else
            return n->val;
    }
    return NULL_Value;
}

bool is_red(RBT *x)
{
    if (x == NULL)
        return BLACK;
    return x->color; // RED == true
}

RBT *rotate_left(RBT *h)
{
    RBT *x = h->r;
    h->r = x->l;
    x->l = h;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

RBT *rotate_right(RBT *h)
{
    RBT *x = h->l;
    h->l = x->r;
    x->r = h;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

void flip_colors(RBT *h)
{
    h->color = RED;
    h->l->color = BLACK;
    h->r->color = BLACK;
}

RBT *RBT_insert(RBT *h, Key key, Value val)
{
    // Insert at bottom and color it red.
    if (h == NULL)
    {
        return create_node(key, val, RED);
    }
    int cmp = compare(key, h->key);
    if (cmp < 0)
    {
        h->l = RBT_insert(h->l, key, val);
    }
    else if (cmp > 0)
    {
        h->r = RBT_insert(h->r, key, val);
    }
    else /*cmp == 0*/
    {
        h->val = val;
    }
    // Lean left.
    if (is_red(h->r) && !is_red(h->l))
    {
        h = rotate_left(h);
    }
    // Balance 4-node.
    if (is_red(h->l) && is_red(h->l->l))
    {
        h = rotate_right(h);
    }
    // Split 4-node.
    if (is_red(h->l) && is_red(h->r))
    {
        flip_colors(h);
    }

    return h;
}

// fazer funcao apara liberar toda a arvore
