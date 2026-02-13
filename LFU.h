#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include "HashTable.h"

#define MAX_CACHE_SIZE 101

struct CacheEntry {
    int key;
    int value;
    int frequency;
    int timestamp;
};

struct LFUCache {
    struct DoubleHashTable hashTable;
    struct CacheEntry entries[MAX_CACHE_SIZE];
    int size;
    int capacity;
    int globalTimestamp;
};

void initLFUCache(struct LFUCache* cache, int capacity);

void lfuSet(struct LFUCache* cache, int key, int value);
int lfuGet(struct LFUCache* cache, int key);

int findEntryIndex(struct LFUCache* cache, int key);
int findMinFreqIndex(struct LFUCache* cache);
void removeEntry(struct LFUCache* cache, int index);

#endif
