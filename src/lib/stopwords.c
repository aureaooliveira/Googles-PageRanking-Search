#include <stdlib.h>
#include "../../headers/stopwords.h"
#include <stdbool.h>
#include <stdio.h>

StopwordTable *swTable_contruct(int size)
{
    StopwordTable *sw = malloc(sizeof(StopwordTable));
    sw->words_array = malloc(sizeof(char *) * size);
    sw->array_size = size;
    sw->n_item = 0;
    return sw;
}

void swTable_add_word(StopwordTable *swt, char *word)
{
    if (swt->array_size <= swt->n_item)
    {
        swt->words_array = realloc(swt->words_array, swt->array_size * 2);
        swt->array_size *= 2;
    }

    swt->words_array[swt->n_item++] = word;
}

void swTable_sorting(StopwordTable *swt)
{
    // implement radix sort
}

bool swTable_has_word(char *word)
{
    // implement binary search
    return false;
}

void swTable_print(StopwordTable *swt)
{
    for (int i = 0; i < swt->n_item; i++)
    {
        printf("%s\n", swt->words_array[i]);
    }
}

void swTable_destroy(StopwordTable *s)
{
    for (int i = 0; i < s->n_item; i++)
    {
        free(s->words_array[i]);
    }
    free(s->words_array);
    free(s);
}
