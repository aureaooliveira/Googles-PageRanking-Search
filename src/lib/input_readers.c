// ler caminho do diretorio pelo argv do console
// dentro do diretorio -> ler arquivo com nome index.txt com nome dos documentos
// dentro do diretorio ->ler arquivo stopwords.txt
// dentro do diretorio ->ler arquivo graph.txt
// dentro do diretorio ->outro diretorio "pages" com os documentos a serem lidos (nomes no index.txt)

#include <stdio.h>
#include <stdlib.h>
#include "../../headers/stopwords.h"
#include "../../headers/graph.h"
#include "../../headers/documents.h"

StopwordTable *stopwords_reader(char *filepath)
{
    FILE *stopword = fopen(filepath, "r");
    StopwordTable *sw_table = swTable_contruct(200);

    if (stopword == NULL)
    {
        printf("erro ao abrir o arquivo %s", filepath);
        exit(1);
    }

    while (!feof(stopword))
    {
        char *word = malloc(sizeof(char) * 50);
        fscanf(stopword, "%s\n", word);
        swTable_add_word(sw_table, word);
    }

    // swTable_print(sw_table);

    fclose(stopword);
    return sw_table;
}

void graph_reader(char *filepath)
{

    FILE *graph_file = fopen(filepath, "r");

    if (graph_file == NULL)
    {
        printf("erro ao abrir o arquivo %s", filepath);
        exit(1);
    }
    fclose(graph_file);
}

DocTable *documents_list_reader(char *filepath)
{
    DocTable *doct = docTable_contruct(1000);

    FILE *index_file = fopen(filepath, "r");
    if (index_file == NULL)
    {
        printf("erro ao abrir o arquivo %s", filepath);
        exit(1);
    }

    while (!feof(index_file))
    {
        char *word = malloc(sizeof(char) * 20);
        fscanf(index_file, "%s\n", word);
        docTable_add_doc(doct, word);
    }
    fclose(index_file);

    return doct;
}

void reader(char *dirpath)
{

    char *index_file = malloc(sizeof(char) * 100);
    char *stopword_file = malloc(sizeof(char) * 100);
    char *graph_file = malloc(sizeof(char) * 100);

    sprintf(index_file, "%s/index.txt", dirpath);
    sprintf(stopword_file, "%s/stopwords.txt", dirpath);
    sprintf(graph_file, "%s/graph.txt", dirpath);

    // printf("%s\n%s\n%s\n", index_file, stopword_file, graph_file);

    StopwordTable *sw_table = stopwords_reader(stopword_file);
    DocTable *doc_table = documents_list_reader(index_file);
    // ordenar tabela de doc antes de fazer o grafo
    docTable_print(doc_table);
    printf("----------------------------------------ORDENA----------------------------------\n");

    docTable_sorting(doc_table);
    docTable_print(doc_table);

    printf("index: %d\n", docTable_has_word(doc_table, "10718.txt"));
    printf("index: %d", docTable_has_word(doc_table, "840.txt"));


    docTable_destroy(doc_table);
    swTable_destroy(sw_table);
    free(index_file);
    free(stopword_file);
    free(graph_file);
}
