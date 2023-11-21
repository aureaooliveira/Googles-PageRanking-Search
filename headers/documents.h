#ifndef _DOCUMENTS_H_
#define _DOCUMENTS_H_
#include <stdbool.h>
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

#endif