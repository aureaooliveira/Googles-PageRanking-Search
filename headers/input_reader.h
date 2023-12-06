#ifndef _INPUT_READER_H_
#define _INPUT_READER_H_
#include "documents.h"
#include "redblack_tree.h"

typedef struct
{
    DocTable *doc_table;
    wordsTree *words_tree;

} allData;

allData reader(char *dirpath);

#endif