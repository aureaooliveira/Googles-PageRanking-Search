#ifndef _INFLUENCY_GRAPH_H_
#define _INFLUENCY_GRAPH_H_

#include "forward_list.h"
#include "documents.h"

typedef struct
{
    int max_size;
    int n_item;
    int *adjacency_list;

} influenced_by; // array de arestas que saem do vertice doc

typedef struct
{

    ForwardList adjacency_list;

} influences; // array das arestas incidentes do vertice doc

typedef struct
{

    influenced_by *influenced_by_arr;
    influences *influences_arr;
    int n_total;
} influencyGraph;

influencyGraph *graph_construct(int n_vertex);
influenced_by influencedby_construct(int n_adjacency);

void add_x_influencedby_y(influencyGraph *graph, int x, int y);
void add_x_influences_y(influencyGraph *graph, int x, int y);

void print_influency_graph(influencyGraph *g, DocTable *dt);
// void calc_PageRank(DocTable *doc, influencyGraph *graph);
void calc_allPageRank(DocTable *doc_table, influencyGraph *graph);
void print_pagerank_values(DocTable *d);
#endif