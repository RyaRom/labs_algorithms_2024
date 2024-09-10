#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *previous;
} Node;

typedef struct CircularLinkedList {
    Node *head;
    int size;
} CircularLinkedList;

void circular_list_add_node(CircularLinkedList *list, int data);

void circular_list_display(const CircularLinkedList *list);

void circular_list_remove_node(CircularLinkedList *list);

CircularLinkedList *newCircularLinkedList();

#endif //CIRCULARLINKEDLIST_H
