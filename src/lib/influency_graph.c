#include "../../headers/influency_graph.h"
#include "../../headers/documents.h"

#include <stdlib.h>
#include <stdio.h>

#define ALPHA 0.85
#define EPSILON 1e-7

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

double abs_value(double val)
{
    if (val < 0)
    {
        val *= -1;
    };
    return val;
}

bool stop_function(DocTable *doc_table, double *new_pageRank)
{
    long double somatory = 0;
    long double aux;

    for (int i = 0; i < doc_table->n_docs; i++)
    {
        somatory += abs_value(new_pageRank[i] - doc_table->doc_array[i].pageRank);

        doc_table->doc_array[i].pageRank = new_pageRank[i]; // atualiza o pr mais atual na tabela oficial
    }

    long double e_value = somatory / doc_table->n_docs;
    // printf("EVALUE == %.9lf\n", e_value);
    // printf("EPSILON == %.9lf\n", EPSILON);

    return (e_value < EPSILON);
}

long double pageRank(int doc, DocTable *doc_table, influencyGraph *graph)
{
    long double somatory = 0;

    ForwardListIterator *iterator = createIterator(graph->influences_arr[doc].adjacency_list);
    // iterador sobre a lista encadeada de IN(doc)

    int current_idx = getNext(iterator);

    while (current_idx != -1)
    {
        long double j_pr_before = docTable_get_pageRank(doc_table, current_idx);
        int j_out_module = graph->influenced_by_arr[current_idx].n_item;

        if (j_out_module == 0)
        {
            printf("ERROR: tinha que haver adjacencia");
            exit(1);
        }
        somatory += (j_pr_before / j_out_module);
        current_idx = getNext(iterator);
    }
    freeIterator(iterator);

    if (graph->influenced_by_arr[doc].n_item == 0)
    {
        long double doc_pr_before = docTable_get_pageRank(doc_table, doc);

        return ((1 - ALPHA) / doc_table->n_docs) + (ALPHA * doc_pr_before) + (ALPHA * somatory);
    }
    else
    {
        return ((1 - ALPHA) / doc_table->n_docs) + (ALPHA * somatory);
    }
}

void calc_allPageRank(DocTable *doc_table, influencyGraph *graph)
{
    double *new_pageRank_arr = malloc(sizeof(double) * doc_table->n_docs);
    int count = 0;
    do
    {
        for (int i = 0; i < doc_table->n_docs; i++)
        {

            new_pageRank_arr[i] = pageRank(i, doc_table, graph);
        }
        count++;

    } while (stop_function(doc_table, new_pageRank_arr) == false);

    // printf("ITERATION COUNTER: %d\n", count);
    free(new_pageRank_arr);

    // calcula todos os valores de page rank
}

void influencyGraph_destroy(influencyGraph *g)
{
    for (int i = 0; i < g->n_total; i++)
    {
        if (g->influenced_by_arr[i].adjacency_list)
        {
            free(g->influenced_by_arr[i].adjacency_list);
        }

        forward_list_destroy(&g->influences_arr[i].adjacency_list);
    }
    free(g->influenced_by_arr);
    free(g->influences_arr);
    free(g);
}

void print_pagerank_values(DocTable *d)
{
    for (int i = 0; i < d->n_docs; i++)
    {
        printf("%d %s %.17lf\n", i, docTable_get_name(d, i), docTable_get_pageRank(d, i));
    }
}
