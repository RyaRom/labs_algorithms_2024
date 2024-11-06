#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "collections/CircularLinkedList.h"
#include "collections/List.h"
#include "utils/Scanner.h"

void collect_sum(List *collector, const CircularLinkedList *list, int lim);

void lab2() {
    CircularLinkedList *list = newCircularLinkedList();
    List *collector = newList();
    read_int_sequence_stdin(&list->abstract_list, list);
    printf("%s", "sequence: ");
    circular_list_display(list);

    printf("Enter variable K: \n");
    const int k = 0;
    scanf("%d", &k);

    collect_sum(collector, list, k);
    list_display(collector);

    list_free(collector);
    circular_list_free(list);

    circular_list_free(list);
    list_free(collector);
}

void collect_sum(List *collector, const CircularLinkedList *list, const int lim) {
    CircularNode *current = circular_list_get_first(list);
    if (current == NULL) return;
    int sum = 0;
    while (sum < lim) {
        const int data = current->data;
        sum += data;
        list_add_node(collector, data);
        current = circular_list_get_next(list, current);
    }
}
