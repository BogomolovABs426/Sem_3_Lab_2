#include "LFU.h"

int findEntryIndex(struct LFUCache* cache, int key) {
    for (int i = 0; i < cache->size; i++) {
        if (cache->entries[i].key == key) {
            return i;
        }
    }
    return -1;
}

void removeEntry(struct LFUCache* cache, int index) {
    if (index < 0 || index >= cache->size) return;

    int key = cache->entries[index].key;
    doubleHashDelete(&cache->hashTable, key);

    
    for (int i = index; i < cache->size - 1; i++) {
        cache->entries[i] = cache->entries[i + 1];
    }
    cache->size--;
}

int findMinFreqIndex(struct LFUCache* cache) {
    if (cache->size == 0) return -1;

    int minFreq = cache->entries[0].frequency;
    int minTime = cache->entries[0].timestamp;
    int minIndex = 0;

    for (int i = 1; i < cache->size; i++) {
        if (cache->entries[i].frequency < minFreq ||
            (cache->entries[i].frequency == minFreq && cache->entries[i].timestamp < minTime)) {
            minFreq = cache->entries[i].frequency;
            minTime = cache->entries[i].timestamp;
            minIndex = i;
        }
    }
    return minIndex;
}

void initLFUCache(struct LFUCache* cache, int capacity) {
    initDoubleHashTable(&cache->hashTable);
    cache->size = 0;
    cache->capacity = capacity;
    cache->globalTimestamp = 0;
}

void lfuSet(struct LFUCache* cache, int key, int value) {
    int index = findEntryIndex(cache, key);

    if (index != -1) {
        
        cache->entries[index].value = value;
        cache->entries[index].frequency++;
        cache->entries[index].timestamp = ++(cache->globalTimestamp);

        
        doubleHashDelete(&cache->hashTable, key);
        doubleHashInsert(&cache->hashTable, key, value);
        return;
    }

    
    if (cache->size >= cache->capacity) {
        int victim = findMinFreqIndex(cache);
        if (victim != -1) {
            removeEntry(cache, victim);
        }
    }

    
    cache->entries[cache->size].key = key;
    cache->entries[cache->size].value = value;
    cache->entries[cache->size].frequency = 1;
    cache->entries[cache->size].timestamp = ++(cache->globalTimestamp);
    cache->size++;

    doubleHashInsert(&cache->hashTable, key, value);
}

int lfuGet(struct LFUCache* cache, int key) {
    int index = findEntryIndex(cache, key);
    if (index == -1) {
        return -1; 
    }

    cache->entries[index].frequency++;
    cache->entries[index].timestamp = ++(cache->globalTimestamp);

    return cache->entries[index].value; 
}
