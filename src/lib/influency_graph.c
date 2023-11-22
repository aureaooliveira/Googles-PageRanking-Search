#include "../../headers/influency_graph.h"
#include "../../headers/documents.h"

#include <stdlib.h>
#include <stdio.h>

influencyGraph *graph_construct(int n_doc)
{
    influencyGraph *g = malloc(sizeof(influencyGraph));
    g->n_total = n_doc;
    g->influenced_by_arr = calloc(n_doc, sizeof(influenced_by));
    g->influences_arr = calloc(n_doc, sizeof(influences));

    return g;
}

influenced_by influencedby_construct(int n_adjacency)
{
    influenced_by array;
    array.adjacency_list = malloc(sizeof(int) * n_adjacency);
    array.max_size = n_adjacency;
    array.n_item = 0;
    return array;
}

void add_x_influencedby_y(influencyGraph *graph, int x, int y)
{
    if (graph->influenced_by_arr[x].n_item == graph->influenced_by_arr[x].max_size)
    {
        printf("ERRO: ADD MAIS QUE O ESPERADO\n");
        exit(1);
    }
    if (x == -1 || y == -1)
    {
        printf("ERRO: NAO ENCONTROU PALAVRA\n");
        exit(1);
    }
    graph->influenced_by_arr[x].adjacency_list[graph->influenced_by_arr[x].n_item++] = y;
}

void add_x_influences_y(influencyGraph *graph, int x, int y)
{
    forward_list_push_front(&graph->influences_arr[x].adjacency_list, y);
}

void print_influency_graph(influencyGraph *g, DocTable *dt)
{
    for (int i = 0; i < g->n_total; i++)
    {
        printf("%s ", docTable_get_name(dt, i));

        /* for (int j = 0; j < g->influenced_by_arr[i].n_item; j++)
         {
             int idx = g->influenced_by_arr[i].adjacency_list[j];
             printf("%s ", docTable_get_name(dt, idx));
         }
         */

        for (int j = 0; j < g->influences_arr[i].adjacency_list.size; j++)
        {
            int idx = forward_list_get(&g->influences_arr[i].adjacency_list, j);
            printf("%s ", docTable_get_name(dt, idx));
        }

        printf("\n");
    }
}

