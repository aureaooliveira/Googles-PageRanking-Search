#include "../../headers/documents.h"
#include <stdlib.h>
#include <stdio.h>

DocTable *docTable_contruct(int size)
{
    DocTable *d = malloc(sizeof(DocTable));
    d->doc_array = malloc(sizeof(char *) * size);
    d->n_docs = 0;
    d->array_size = size;
    return d;
}

document document_construct(char *doc_name)
{
    document d;
    d.name = doc_name;
    return d;
}

void docTable_add_doc(DocTable *doct, char *word)
{
    // document d = document_construct(word);
    if (doct->array_size <= doct->n_docs)
    {
        doct->doc_array = realloc(doct->doc_array, doct->array_size * 2);
        doct->array_size *= 2;
    }

    doct->doc_array[doct->n_docs++] = word;
}

void docTable_sorting(DocTable *doct)
{
    // implement radix sort
}
bool docTable_has_word(char *word)
{
    // implement binary search
}
void docTable_print(DocTable *doct)
{
    for (int i = 0; i < doct->n_docs; i++)
    {
        printf("%s\n", doct->doc_array[i]);
    }
}

void docTable_destroy(DocTable *d)
{
    for (int i = 0; i < d->n_docs; i++)
    {
        free(d->doc_array[i]);
    }
    free(d->doc_array);

    free(d);
}
