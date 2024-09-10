//
// Created by locadm on 9/11/2024.
//

#include "List.h"

#include <stdio.h>
#include <stdlib.h>

List *newList() {
    List *list = malloc(sizeof(List));
    if (list == NULL) exit(EXIT_FAILURE);
    list->head = NULL;
    list->size = 0;
    return list;
}

void list_add_node(List *list, int data) {
    if (list == NULL) return;
    ListNode *newNode = malloc(sizeof(ListNode));
    if (newNode == NULL) exit(EXIT_FAILURE);
    newNode->data = data;
    newNode->next = NULL;

    if (list->size == 0) {
        list->head = newNode;
    } else {
        ListNode *tail = getTail(list);
        if (tail == NULL) exit(EXIT_FAILURE);
        tail->next = newNode;
    }

    list->size++;
}

void list_display(const List *list) {
    if (list == NULL) return;
    const int size = list->size;
    const ListNode *current = list->head;
    for (int i = 0; i < size; ++i) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

ListNode *getTail(const List *list) {
    if (list == NULL) return NULL;
    const int size = list->size;
    const ListNode *current = list->head;
    for (int i = 0; i < size - 1; ++i) {
        current = current->next;
    }
    return current;
}
