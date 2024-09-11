#include "CircularLinkedList.h"

#include <stdio.h>
#include <stdlib.h>

CircularLinkedList *newCircularLinkedList() {
    CircularLinkedList *newCircularLinkedList = malloc(sizeof(CircularLinkedList));
    if (newCircularLinkedList == NULL) exit(EXIT_FAILURE);
    newCircularLinkedList->head = NULL;
    newCircularLinkedList->size = 0;

    AbstractList *list = &(newCircularLinkedList->abstract_list);

    list->add_int_elem = circular_list_add_node;
    list->display = circular_list_display;
    list->remove_int_elem = circular_list_remove_node;
    list->get_int_elem = circular_list_get;
    return newCircularLinkedList;
}

void circular_list_add_node(CircularLinkedList *list, const int data) {
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

void circular_list_display(const CircularLinkedList *list) {
    if (circular_list_is_empty(list)) return;
    const int size = list->size;
    const Node *current = list->head;
    for (int i = 0; i < size; ++i) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void circular_list_remove_last(CircularLinkedList *list) {
    if (circular_list_is_empty(list)) return;
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

void circular_list_remove_internal(const CircularLinkedList *list, Node *current) {
    if (circular_list_is_empty(list) || current == NULL) return;
    Node *previous = current->previous;
    Node *next = current->next;
    previous->next = next;
    next->previous = previous;
    free(current);
}

void circular_list_remove_node(CircularLinkedList *list, int data) {
    if (circular_list_is_empty(list)) return;
    if (list->size == 1 && list->head->data == data) {
        list->head = NULL;
        list->size = 0;
        return;
    }

    Node *head = list->head;
    if (head->data == data) {
        list->head = head->next;
        circular_list_remove_internal(list, head);
        list->size--;
        return;
    }

    Node *current = head->next;
    for (int i = 0; i < list->size; i++) {
        if (current->data == data) {
            circular_list_remove_internal(list, current);
            break;
        }
        current = current->next;
    }

    list->size--;
}

Node *circular_list_get(const CircularLinkedList *list, int data) {
    if (circular_list_is_empty(list)) return NULL;
    Node *current = list->head;
    for (int i = 0; i < list->size; i++) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Node *circular_list_get_first(const CircularLinkedList *list) {
    if (circular_list_is_empty(list)) return NULL;
    return list->head;
}

Node *circular_list_get_next(const CircularLinkedList *list, const Node *current) {
    if (circular_list_is_empty(list) || current == NULL) return NULL;
    return current->next;
}

int circular_list_is_empty(const CircularLinkedList *list) {
    if (list == NULL || list->size == 0) return 1;
    return 0;
}

void circular_list_free(CircularLinkedList *list) {
    if (list == NULL) return;
    Node *current = list->head;
    for (int i = 0; i < list->size; i++) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}
