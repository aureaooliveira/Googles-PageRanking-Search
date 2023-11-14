#include "../../headers/graph.h"
#include <stdlib.h>

Graph *graph_construct(int n_vertex)
{
    Graph *g = malloc(sizeof(Graph));
    g->n_vertex = n_vertex;
    g->vertex_list = malloc(sizeof(graphNode) * n_vertex);
    return g;
}

graphNode graphNode_construct(int id, int n_adjacency)
{
    graphNode g;
    g.n_djacentsNode = n_adjacency;
    g.idx_doc = id;
    g.adjacency_list = malloc(sizeof(int) * n_adjacency);
    return g;
}

void graph_add_adjnode(Graph *g, int vtx_id, int adj_id, int arr_counter)
{
    g->vertex_list[vtx_id].adjacency_list[arr_counter] = adj_id;
    // lembrar de entrar sempre com o valor incrementado!!
}
