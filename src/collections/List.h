//
// Created by locadm on 9/11/2024.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "AbstractList.h"

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head;
    int size;
    AbstractList abstract_list;
} List;

void list_add_node(List *list, int data);

void list_display(const List *list);

ListNode *getTail(const List *list);

void list_remove_node(List *list, int data);

ListNode *list_get(const List *list, int data);

List *newList();

void list_free(List *list);

int list_is_empty(const List *list);
#endif //LINKEDLIST_H
