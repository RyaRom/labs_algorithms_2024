#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H
#include "AbstractList.h"

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *previous;
} CircularNode;

typedef struct CircularLinkedList {
    CircularNode *head;
    int size;
    AbstractList abstract_list;
} CircularLinkedList;

void circular_list_add_node(CircularLinkedList *list, int data);

void circular_list_display(const CircularLinkedList *list);

void circular_list_remove_last(CircularLinkedList *list);

void circular_list_remove_node(CircularLinkedList *list, int data);

CircularNode *circular_list_get(const CircularLinkedList *list, int data);

CircularNode *circular_list_get_first(const CircularLinkedList *list);

CircularNode *circular_list_get_next(const CircularLinkedList *list, const CircularNode *current);

int circular_list_is_empty(const CircularLinkedList *list);

void circular_list_free(CircularLinkedList *list);

CircularLinkedList *newCircularLinkedList();

#endif //CIRCULARLINKEDLIST_H
