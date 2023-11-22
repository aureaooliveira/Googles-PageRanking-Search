#include <stdlib.h>
#include "../../headers/stopwords.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

swTree *swTree_construct()
{
    return NULL;
}

swTree *create_sw_node(Key key, bool color)
{
    swTree *node = malloc(sizeof(swTree));
    node->key = key;

    node->color = RED;
    node->l = NULL;
    node->r = NULL;
    return node;
}

int compare_sw(char *k1, char *k2)
{
    return strcasecmp(k1, k2);
}

bool search_sw(swTree *n, Key key)
{

    while (n != NULL)
    {
        int cmp;
        cmp = compare_sw(key, n->key);
        if (cmp < 0)
            n = n->l;
        else if (cmp > 0)
            n = n->r;
        else
            return true;
    }
    return false;
}

bool sw_is_red(swTree *x)
{
    if (x == NULL)
        return BLACK;
    return x->color; // RED == true
}

swTree *sw_rotate_left(swTree *h)
{
    swTree *x = h->r;
    h->r = x->l;
    x->l = h;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

swTree *sw_rotate_right(swTree *h)
{
    swTree *x = h->l;
    h->l = x->r;
    x->r = h;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

void sw_flip_colors(swTree *h)
{
    h->color = RED;
    h->l->color = BLACK;
    h->r->color = BLACK;
}

swTree *swTree_insert(swTree *h, Key key)
{
    // Insert at bottom and color it red.
    if (h == NULL)
    {
        return create_sw_node(key, RED);
    }
    int cmp = compare_sw(key, h->key);
    if (cmp < 0)
    {
        h->l = swTree_insert(h->l, key);
    }
    else if (cmp > 0)
    {
        h->r = swTree_insert(h->r, key);
    }
    else /*cmp == 0*/
    {
        // printf("erro: nao deveria ter 2 stopwords iguais: %s %s\n", key, h->key);
        free(key);
        
    }
    // Lean left.
    if (sw_is_red(h->r) && !sw_is_red(h->l))
    {
        h = sw_rotate_left(h);
    }
    // Balance 4-node.
    if (sw_is_red(h->l) && sw_is_red(h->l->l))
    {
        h = sw_rotate_right(h);
    }
    // Split 4-node.
    if (sw_is_red(h->l) && sw_is_red(h->r))
    {
        sw_flip_colors(h);
    }

    return h;
}

void free_sw_Node(swTree *node)
{
    free(node->key);
    free(node);
}

void free_swTree(swTree *root)
{
    if (root != NULL)
    {

        free_swTree(root->l);
        free_swTree(root->r);
        printf("%s\n", root->key);
        // print_value(root->val);
        free_sw_Node(root);
    }
}
