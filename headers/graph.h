#ifndef _GRAPH_H_
#define _GRAPH_H_
typedef struct
{
    int idx_doc;
    int n_djacentsNode;
    int *adjacency_list;

} graphNode;

typedef struct
{
    int n_vertex;
    graphNode *vertex_list;
} Graph;

Graph *graph_construct(int n_vertex);
void graph_add_adjnode(Graph *g, int vtx_id, int adj_id, int arr_counter);

#endif