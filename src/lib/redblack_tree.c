#include "../../headers/redblack_tree.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define NULL_Value NULL
#define DOC_ARR_SIZE 5

// TODO
//- tratar casos de print em valores NULL (nao existe na arvore)

RBT *RBT_contruct()
{
    RBT *node = NULL;
    return node;
}

RBT *create_node(Key key, Value val, bool color)
{
    RBT *node = malloc(sizeof(RBT));
    node->key = key;
    node->val.doc_array = malloc(sizeof(int) * DOC_ARR_SIZE);

    node->val.max_size = DOC_ARR_SIZE;
    node->color = RED;
    node->l = NULL;
    node->r = NULL;

    node->val.doc_array[0] = val;
    node->val.n_docs = 1;
    return node;
}

int compare(Key k1, Key k2)
{
    return strcasecmp(k1, k2);
}

doc_array *search(RBT *n, Key key)
{
    if (!key)
    {
        return NULL;
    }

    while (n != NULL)
    {
        int cmp;
        cmp = compare(key, n->key);
        if (cmp < 0)
            n = n->l;
        else if (cmp > 0)
            n = n->r;
        else
            return &n->val;
    }
    return NULL;
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

void add_doc_to_array(RBT *node, Value val)
{
    if (val == node->val.doc_array[node->val.n_docs - 1])
    {
        return;
    }
    if (node->val.max_size == node->val.n_docs)
    {
        // realloc;
        node->val.max_size *= 2;
        node->val.doc_array = realloc(node->val.doc_array, sizeof(int) * node->val.max_size);
    }

    node->val.doc_array[node->val.n_docs++] = val;
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
        // h->val = val;
        add_doc_to_array(h, val);
        free(key);
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

void print_value(doc_array val)
{

    printf("docs: ");
    for (int i = 0; i < val.n_docs; i++)
    {
        printf("%d ", val.doc_array[i]);
    }
    printf("\n");
}

// fazer funcao apara liberar toda a arvore

void freeNode(RBT *node)
{
    free(node->key);
    free(node->val.doc_array);
    free(node);
}

void freeTree(RBT *root)
{
    if (root != NULL)
    {

        freeTree(root->l);
        freeTree(root->r);
        // printf("%s ", root->key);
        // print_value(root->val);
        freeNode(root);
    }
}

