#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 101
#define DELETED_MARKER -1
#define EMPTY_MARKER -2

struct DoubleHashTable {
    int keys[TABLE_SIZE];
    int values[TABLE_SIZE];
    int size;
    int collisions;
};

void initDoubleHashTable(struct DoubleHashTable* ht);
int doubleHashInsert(struct DoubleHashTable* ht, int key, int value);
int doubleHashSearch(struct DoubleHashTable* ht, int key, int* value);
int doubleHashDelete(struct DoubleHashTable* ht, int key);

#endif
