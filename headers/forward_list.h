
#ifndef _FORWARD_forward_list_H_
#define _FORWARD_forward_list_H_

typedef int data_type;
typedef struct ForwardListIterator ForwardListIterator;

typedef struct Node
{
    data_type value;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    int size;
} ForwardList;

ForwardList *forward_list_construct();

int forward_list_size(ForwardList *l);

void forward_list_push_front(ForwardList *l, data_type data);

void forward_list_print(ForwardList *l, void (*print_fn)(data_type));
data_type forward_list_get(ForwardList *l, int i);

void forward_list_destroy(ForwardList *l);

void freeIterator(ForwardListIterator *iterator);
ForwardListIterator *createIterator(ForwardList l);
int getNext(ForwardListIterator *iterator);

#endif