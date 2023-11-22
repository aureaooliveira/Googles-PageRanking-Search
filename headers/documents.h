#ifndef _DOCUMENTS_H_
#define _DOCUMENTS_H_
#include <stdbool.h>
// #include "influency_graph.h"
typedef struct
{
    char *name;
    double pageRank;
} document;

typedef struct
{
    document *doc_array;
    int array_size;
    int n_docs;

} DocTable;

DocTable *docTable_contruct(int size);
void docTable_add_doc(DocTable *doct, char *word);
void docTable_sorting(DocTable *doct);
int docTable_has_word(DocTable *doct, char *word);
void docTable_print(DocTable *doct);
void docTable_destroy(DocTable *d);
void docTable_sorting(DocTable *doct);

char *docTable_get_name(DocTable *d, int idx);
double docTable_get_pageRank(DocTable *d, int idx);

#endif