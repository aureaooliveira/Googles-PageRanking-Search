// ler caminho do diretorio pelo argv do console
// dentro do diretorio -> ler arquivo com nome index.txt com nome dos documentos
// dentro do diretorio ->ler arquivo stopwords.txt
// dentro do diretorio ->ler arquivo graph.txt
// dentro do diretorio ->outro diretorio "pages" com os documentos a serem lidos (nomes no index.txt)

#include <stdio.h>
#include <stdlib.h>
#include "../../headers/stopwords.h"
#include "../../headers/influency_graph.h"
#include "../../headers/documents.h"
#include "../../headers/redblack_tree.h"
#include "../../headers/input_reader.h"



swTree *stopwords_reader(char *filepath)
{
    FILE *stopword = fopen(filepath, "r");
    swTree *sw_tree = swTree_construct();

    if (stopword == NULL)
    {
        printf("erro ao abrir o arquivo %s", filepath);
        exit(1);
    }

    while (!feof(stopword))
    {
        char *word = malloc(sizeof(char) * 20);
        fscanf(stopword, "%s\n", word);
        sw_tree = swTree_insert(sw_tree, word);
    }

    fclose(stopword);
    return sw_tree;
}

influencyGraph *graph_reader(char *filepath, DocTable *doc_table)
{

    FILE *graph_file = fopen(filepath, "r");

    if (graph_file == NULL)
    {
        printf("erro ao abrir o arquivo %s", filepath);
        exit(1);
    }

    influencyGraph *graph = graph_construct(doc_table->n_docs);

    char *current_docName = malloc(sizeof(char) * 20);
    char *aux_docName = malloc(sizeof(char) * 20);

    while (!feof(graph_file))
    {
        int n_adjacency = 0;
        fscanf(graph_file, "%s %d ", current_docName, &n_adjacency);

        int current_docIdx = docTable_has_word(doc_table, current_docName);

        graph->influenced_by_arr[current_docIdx] = influencedby_construct(n_adjacency);

        for (int i = 0; i < n_adjacency; i++)
        {
            fscanf(graph_file, "%s ", aux_docName);
            int aux_docIdx = docTable_has_word(doc_table, aux_docName);
            // add o int aux_id no vetor da posicao influeced_by[current_id]
            add_x_influencedby_y(graph, current_docIdx, aux_docIdx);

            // add no vetor influences[aux_id] o valor int current_id
            add_x_influences_y(graph, aux_docIdx, current_docIdx);
        }
    }

    fclose(graph_file);
    free(current_docName);
    free(aux_docName);

    return graph;
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

wordsTree *words_reader(DocTable *doc_table, swTree *sw_tree, char *dirpath)
{
    char *document_file_name = malloc(sizeof(char) * 100);

    wordsTree *allWords_tree = RBT_contruct();

    for (int i = 0; i < doc_table->n_docs; i++)
    {
        sprintf(document_file_name, "%s/pages/%s", dirpath, doc_table->doc_array[i].name);

        FILE *doc_file = fopen(document_file_name, "r");
        if (doc_file == NULL)
        {
            printf("erro ao abrir o arquivo %s", document_file_name);
            exit(1);
        }

        while (!feof(doc_file))
        {
            char *word = malloc(sizeof(char *) * 15);
            fscanf(doc_file, "%s ", word);

            if (search_sw(sw_tree, word))
            {
                free(word);
            }
            else
            {
                allWords_tree = RBT_insert(allWords_tree, word, i);
            }
        }

        fclose(doc_file);
    }

    free(document_file_name);

    return allWords_tree;
}

allData reader(char *dirpath)
{

    char *index_file = malloc(sizeof(char) * 100);
    char *stopword_file = malloc(sizeof(char) * 100);
    char *graph_file = malloc(sizeof(char) * 100);

    sprintf(index_file, "%s/index.txt", dirpath);
    sprintf(stopword_file, "%s/stopwords.txt", dirpath);
    sprintf(graph_file, "%s/graph.txt", dirpath);


    swTree *sw_tree = stopwords_reader(stopword_file);

    DocTable *doc_table = documents_list_reader(index_file);

    docTable_sorting(doc_table);//by lexical order

    influencyGraph *influency_graph = graph_reader(graph_file, doc_table);

    calc_allPageRank(doc_table, influency_graph);
    influencyGraph_destroy(influency_graph);

    docTable_sorted_by_pageRank(doc_table);
    wordsTree *allWords_tree = words_reader(doc_table, sw_tree, dirpath);

    allData data;
    data.doc_table = doc_table;
    data.words_tree = allWords_tree; 
    //docTable_destroy(doc_table);
    free_swTree(sw_tree);
    //freeTree(allWords_tree);
    free(index_file);
    free(stopword_file);
    free(graph_file);
    return data;
}
