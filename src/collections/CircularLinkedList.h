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

void addNode(CircularLinkedList *list, int data);

void display(const CircularLinkedList *list);

void removeNode(CircularLinkedList *list);

CircularLinkedList *newCircularLinkedList();

#endif //CIRCULARLINKEDLIST_H
