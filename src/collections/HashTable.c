#include "HashTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <utils/Types.h>
static const HashEntry _REMOVED = {NULL, NULL};

int _simple_hash(char *str);

int _get_index_from_key(KeyType *key, HashTable *table);

int _get_last_free_index_from_key(KeyType *key, HashTable *table);

void _hashtable_overflow(HashTable *table);

int _get_index_from_key(KeyType *key, HashTable *table) {
    const int hashed_first = table->hash_func_1(key);
    int hashed_second = table->hash_func_2(key);
    if (hashed_second == 0) {
        hashed_second = 1;
    }
    for (int i = 0; i < table->segments; ++i) {
        const int index = (hashed_first + i * hashed_second) % table->segments;
        if (table->nodes[index] == &_REMOVED) {
            continue;
        }
        if (table->nodes[index] == NULL
            || table->nodes[index]->key == key) {
            return index;
        }
    }
    _hashtable_overflow(table);
    return _get_index_from_key(key, table);
}

//does not skip REMOVED nodes
int _get_last_free_index_from_key(KeyType *key, HashTable *table) {
    const int hashed_first = table->hash_func_1(key);
    const int hashed_second = table->hash_func_2(key);
    for (int i = 0; i < table->segments; ++i) {
        const int index = (hashed_first + i * hashed_second) % table->segments;
        if (table->nodes[index] == NULL
            || table->nodes[index] == &_REMOVED
            || table->nodes[index]->key == key) {
            return index;
        }
    }
    _hashtable_overflow(table);
    return _get_index_from_key(key, table);
}

int _simple_hash(char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = hash * 31 + *str;
        str++;
    }
    return hash;
}


void _hashtable_overflow(HashTable *table) {
    const int old_size = table->segments;
    HashEntry **old_nodes = table->nodes;
    table->segments = old_size * 1.25;
    table->nodes = calloc(table->segments, sizeof(HashEntry *));

    //rehashing
    for (int i = 0; i < old_size; ++i) {
        HashEntry *node = old_nodes[i];
        if (node == NULL || node == &_REMOVED) {
            continue;
        }

        const int new_index = _get_index_from_key(node->key, table);
        table->nodes[new_index] = node;
    }

    free(old_nodes);
}


HashTable *new_hash_table() {
    HashTable *new_hash_table = malloc(sizeof(HashTable));
    new_hash_table->hash_func_1 = _simple_hash;
    new_hash_table->hash_func_2 = _simple_hash;
    new_hash_table->segments = _INIT_SEGMENTS;
    new_hash_table->nodes = calloc(new_hash_table->segments, sizeof(HashEntry *));
    return new_hash_table;
}


bool hashtable_put(HashTable *table, KeyType *key, ElementType *value) {
    const int index = _get_last_free_index_from_key(key, table);
    HashEntry *entry = table->nodes[index];
    if (entry == NULL || entry == &_REMOVED) {
        entry = malloc(sizeof(HashEntry));
        entry->key = key;
        entry->value = value;
        table->nodes[index] = entry;
        return false;
    }

    entry->value = value;
    return true;
}

ElementType *hashtable_get(HashTable *table, KeyType *key) {
    const int index = _get_index_from_key(key, table);
    HashEntry *entry = table->nodes[index];
    if (entry == NULL) {
        return NULL;
    }
    return entry->value;
}

ElementType *hashtable_remove(HashTable *table, KeyType *key) {
    const int index = _get_index_from_key(key, table);
    HashEntry *entry = table->nodes[index];
    if (entry == NULL) {
        return NULL;
    }
    ElementType *oldVal = entry->value;
    free(entry);
    table->nodes[index] = &_REMOVED;
    return oldVal;
}

void hashtable_clear(HashTable *table) {
    for (int i = 0; i < table->segments; ++i) {
        if (table->nodes[i] != NULL && table->nodes[i] != &_REMOVED) {
            free(table->nodes[i]);
        }
    }
    free(table->nodes);
    table->segments = _INIT_SEGMENTS;
    table->nodes = calloc(table->segments, sizeof(HashEntry *));
}

void hashtable_print(const HashTable *table) {
    for (int i = 0; i < table->segments; ++i) {
        const HashEntry *entry = table->nodes[i];
        if (entry != NULL && entry->value != NULL
            && entry != &_REMOVED) {
            printf("%d ", *entry->value);
        }
    }
    printf("\n");
}

bool hashtable_contains_key(HashTable *table, KeyType *key) {
    const int index = _get_index_from_key(key, table);
    if (table->nodes[index] == NULL) {
        return false;
    }
    return true;
}