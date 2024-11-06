#ifndef HASHTABLE_H
#define HASHTABLE_H
#define _INIT_SEGMENTS 2500
#include <stdlib.h>
#include <utils/Types.h>
typedef int ElementType;
typedef char KeyType;

typedef struct HashEntry {
    KeyType *key;
    ElementType *value;
} HashEntry;

typedef struct HashTable {
    HashEntry **nodes;

    int (*hash_func_1)(KeyType *key);

    int (*hash_func_2)(KeyType *key);

    int segments;
} HashTable;


HashTable *new_hash_table();

/**
 * Returns a true if previous element was overwritten
 */
bool hashtable_put(HashTable *table, KeyType *key, ElementType *value);

bool hashtable_contains_key(HashTable *table, KeyType *key);

/**
 * Returns a pointer to found element with that key or Null
 */
ElementType *hashtable_get(HashTable *table, KeyType *key);

/**
 * Returns a pointer to removed element with that key or Null
 */
ElementType *hashtable_remove(HashTable *table, KeyType *key);

void hashtable_clear(HashTable *table);

void hashtable_print(const HashTable *table);


#endif //HASHTABLE_H
