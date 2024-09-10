#include "CircularLinkedList.h"

#include <stdio.h>
#include <stdlib.h>

CircularLinkedList *newCircularLinkedList() {
    CircularLinkedList *newCircularLinkedList = malloc(sizeof(CircularLinkedList));
    if (newCircularLinkedList == NULL) exit(EXIT_FAILURE);
    newCircularLinkedList->head = NULL;
    newCircularLinkedList->size = 0;
    return newCircularLinkedList;
}

void addNode(CircularLinkedList *list, const int data) {
    if (list == NULL) return;
    const int size = list->size;

    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) exit(EXIT_FAILURE);
    newNode->data = data;

    if (size == 0) {
        newNode->next = newNode;
        newNode->previous = newNode;
        list->head = newNode;
    } else {
        Node *head = list->head;
        Node *tail = head->previous;
        tail->next = newNode;
        head->previous = newNode;
        newNode->next = head;
        newNode->previous = tail;
    }
    list->size++;
}

void display(const CircularLinkedList *list) {
    if (list == NULL) return;
    const int size = list->size;
    const Node *current = list->head;
    for (int i = 0; i < size; ++i) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void removeNode(CircularLinkedList *list) {
    if (list == NULL || list->size == 0) return;
    if (list->size == 1) {
        list->head = NULL;
        list->size = 0;
        return;
    }

    Node *head = list->head;
    Node *tail = head->previous;
    Node *newTail = tail->previous;

    head->previous = newTail;
    newTail->next = head;
    free(tail);

    list->size--;
}
