#include <stdio.h>
#include <stdlib.h>

#include "collections/HashTable.h"

void lab4() {
    HashTable *table = new_hash_table();
    int val1 = 1;
    int val2 = 2;
    int val3 = 3;
    hashtable_put(table, "1", &val1);
    hashtable_put(table, "2", &val2);
    hashtable_put(table, "3", &val3);
    hashtable_print(table);
    hashtable_remove(table, "1");
    hashtable_remove(table, "2");
    hashtable_remove(table, "3");
    hashtable_print(table);
    hashtable_put(table, "1", &val1);
    hashtable_put(table, "2", &val2);
    hashtable_put(table, "3", &val3);
    hashtable_print(table);
}
