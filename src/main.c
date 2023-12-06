#include <stdio.h>
#include "../headers/input_reader.h"
#include "../headers/redblack_tree.h"
#include <string.h>
#include <stdlib.h>

/*
  infos:

   - Doc_Table ordenada por ordem do pageRanking e lexical
   - StopWord como um array (ERRADO) -> implementar em uma hash table
   - implementar a busca de varios termos juntos
   - estudar as entradas e saidas

 */

doc_array *compare_intersection(doc_array *array_temp, doc_array *array2)
{

  if (array_temp == NULL || array2 == NULL)
  {
    return NULL;
  }

  int j = 0, i = 0;
  doc_array *intersection = malloc(sizeof(doc_array));
  intersection->n_docs = 0;

  if (array_temp->n_docs > array2->n_docs)
  {
    intersection->max_size = array_temp->n_docs;
    intersection->doc_array = malloc(sizeof(int) * array_temp->n_docs);
  }
  else
  {
    intersection->max_size = array2->n_docs;
    intersection->doc_array = malloc(sizeof(int) * array2->n_docs);
  }

  while (i < array_temp->n_docs && j < array2->n_docs)
  {
    int id_array_temp = array_temp->doc_array[i];
    int id_array2 = array2->doc_array[j];

    if (id_array_temp == id_array2)
    {
      intersection->doc_array[intersection->n_docs++] = id_array2;
      j++;
    }
    else if (id_array_temp > id_array2)
    {
      j++;
    }
    else
    {
      i++;
    }
  }
  if (array_temp != array2)
  {
    free(array_temp->doc_array);
    free(array_temp);
  }
  if (intersection->n_docs == 0)
  {
    free(intersection->doc_array);
    free(intersection);
    return NULL;
  }

  return intersection;
}

void print_result_of_search(doc_array *docs, DocTable *doc_table)
{
  if (docs == NULL)
  {
    printf("pages:\n");
    printf("pr:\n");
  }
  else
  {
    printf("pages:");

    for (int i = 0; i < docs->n_docs; i++)
    {
      printf(" %s", docTable_get_name(doc_table, docs->doc_array[i]));
    }

    printf("\n");
    printf("pr:");
    for (int i = 0; i < docs->n_docs; i++)
    {
      printf(" %lf", docTable_get_pageRank(doc_table, docs->doc_array[i]));
    }
    printf("\n");
  }
}

int main(int argc, char **argv)
{

  allData data_storage = reader(argv[1]);
  char line[100];
  char *word = malloc(sizeof(char) * 20);
  char *allocated_word = word;
  char *buffer = malloc(sizeof(char *) * 100);
  while (!feof(stdin))
  {

    buffer = fgets(line, sizeof(line), stdin);
    if (!buffer)
    {
      break;
    }
    // retirando o \n
    printf("seach: %s", line);
    line[strlen(line) - 1] = '\0';

    word = strtok(line, " ");

    doc_array *result1 = search(data_storage.words_tree, word);
    doc_array *result = compare_intersection(result1, result1);

    while (word)
    {
      word = strtok(NULL, " ");
      if (word)
      {
        doc_array *result1 = search(data_storage.words_tree, word);
        result = compare_intersection(result, result1);
      }
    }

    print_result_of_search(result, data_storage.doc_table);
    if (result)
    {
      free(result->doc_array);
      free(result);
    }
  }

  free(allocated_word);
  docTable_destroy(data_storage.doc_table);
  freeTree(data_storage.words_tree);

  return 0;
}
