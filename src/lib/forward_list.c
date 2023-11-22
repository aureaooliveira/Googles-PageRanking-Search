#include "../../headers/forward_list.h"

#include <stdlib.h>
#include <stdio.h>

typedef int data_type;

Node *node_construct(data_type value, Node *next)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->value = value;
    n->next = next;
    return n;
}

void node_destroy(Node *n)
{
    free(n);
}

void node_print(Node *n)
{
    printf("%d", n->value);
}

ForwardList *forward_list_construct()
{
    ForwardList *list = (ForwardList *)malloc(sizeof(ForwardList));
    list->size = 0;
    list->head = 0;
    return list;
}

int forward_list_size(ForwardList *l)
{
    return l->size;
}

void forward_list_push_front(ForwardList *l, data_type data)
{
    Node *newNode = node_construct(data, l->head);
    l->size++;
    l->head = newNode;
}
void forward_list_print(ForwardList *l, void (*print_fn)(data_type))
{

    printf("[");

    Node *head = l->head;

    for (int i = 0; i < l->size; i++)
    {

        node_print(l->head);

        if (l->head->next)
        {

            printf(", ");
        }

        l->head = l->head->next;
    }
    printf("]");
    l->head = head;
}

data_type forward_list_get(ForwardList *l, int i)
{

    Node *head = l->head;
    while (i)
    {
        if (!l->head->next)
        {
            break;
        }

        l->head = l->head->next;
        i--;
    }

    data_type val = l->head->value;
    l->head = head;

    return val;
}

data_type forward_list_pop_front(ForwardList *l)
{
    data_type val = l->head->value;
    Node *head = l->head->next;
    node_destroy(l->head);
    l->head = head;
    l->size--;
    return val;
}

ForwardList *forward_list_reverse(ForwardList *l)
{
    ForwardList *reverseList = forward_list_construct();
    for (int i = 0; i < l->size; i++)
    {

        reverseList->head = node_construct(forward_list_get(l, i), reverseList->head);
        // printf("i = %d,val = %d\n",i, forward_list_get(l,i));
    }
    reverseList->size = l->size;
    return reverseList; // list->head->next = 0;
}

void forward_list_remove(ForwardList *l, data_type val)
{
    Node *head = l->head;
    Node *atual = l->head;
    Node *anterior = l->head;
    // consertar funcao para remover outros itens da lista que nao seja o head
    // função apenas excliidno primeiro intem

    for (int i = 0; i < l->size; i++)
    {
        printf("atual val = %d\n", atual->value);

        if (atual->value == val)
        {
            printf("entrou");

            if (atual == l->head)
            {
                head = atual->next;
            }
            else
            {

                anterior->next = atual->next;
            }

            node_destroy(atual);
            l->size--;
            // liberar o nó atual
            break;
        }
        anterior = atual;
        atual = atual->next;
    }
    l->head = head;
}

void forward_list_destroy(ForwardList *l)
{

    // printf("endereco head:%p\n",l->head);

    Node *atual = l->head;

    while (atual != NULL)
    {
        Node *proximo = atual->next;
        node_destroy(atual);
        atual = proximo;
    }
    l->head = NULL;
}

struct ForwardListIterator
{
    Node *current;
};

ForwardListIterator *createIterator(ForwardList l)
{
    ForwardListIterator *iterator = (ForwardListIterator *)malloc(sizeof(ForwardListIterator));
    iterator->current = l.head;
    return iterator;
}

int getNext(ForwardListIterator *iterator)
{
    if (iterator->current == NULL)
    {
        // Retorna um valor especial (por exemplo, -1) para indicar o final da lista
        return -1;
    }
    else
    {
        int data = iterator->current->value;
        iterator->current = iterator->current->next;
        return data;
    }
}

void freeIterator(ForwardListIterator *iterator)
{
    free(iterator);
}