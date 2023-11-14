#ifndef _STOPWORD_H_
#define _STOPWORD_H_
#include <stdbool.h>

typedef struct
{
    char **words_array;
    int array_size;
    int n_item;
} StopwordTable;

StopwordTable *swTable_contruct(int size);
void swTable_add_word(StopwordTable *swt, char *word);
void swTable_sorting(StopwordTable *swt);
bool swTable_has_word(char *word);
void swTable_print(StopwordTable *swt);
void swTable_destroy(StopwordTable *s);

#endif