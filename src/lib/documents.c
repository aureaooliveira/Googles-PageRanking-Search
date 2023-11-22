#include "../../headers/documents.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

DocTable *docTable_contruct(int size)
{
    DocTable *d = malloc(sizeof(DocTable));
    d->doc_array = malloc(sizeof(document) * size);
    d->n_docs = 0;
    d->array_size = size;
    return d;
}

document document_construct(char *doc_name)
{
    document d;
    d.name = doc_name;
    d.pageRank = 0;
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

    doct->doc_array[doct->n_docs++] = document_construct(word);
}

int compare_doc(const void *v1, const void *v2)
{
    document d1 = *(document *)v1;
    document d2 = *(document *)v2;

    return strcmp(d1.name, d2.name);
}

void docTable_sorting(DocTable *doct)
{
    qsort(doct->doc_array, doct->n_docs, sizeof(document), compare_doc);
    // implement radix sort
}

int binarySearch(document *arr, int l, int r, char *doc_name)
{
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        int result = strcmp(arr[m].name, doc_name);

        // Check if x is present at mid
        if (!result) // func return 0 if is equal
            return m;

        // If x greater, ignore left half
        if (result < 0)
            l = m + 1;

        // If x is smaller, ignore right half
        else
            r = m - 1;
    }

    // If we reach here, then element was not present
    return -1;
}
int docTable_has_word(DocTable *doct, char *word)
{
    return binarySearch(doct->doc_array, 0, doct->n_docs, word);

    // implement binary search
}

void docTable_print(DocTable *doct)
{
    for (int i = 0; i < doct->n_docs; i++)
    {
        printf("%s\n", doct->doc_array[i].name);
    }
}

char *docTable_get_name(DocTable *d, int idx)
{
    return d->doc_array[idx].name;
}

void docTable_destroy(DocTable *d)
{
    for (int i = 0; i < d->n_docs; i++)
    {
        free(d->doc_array[i].name);
    }
    free(d->doc_array);

    free(d);
}

