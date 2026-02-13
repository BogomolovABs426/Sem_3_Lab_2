#include "HashTable.h"
#include <iostream>
using namespace std;

int cuckooH1(int key) {
    return key % TABLE_SIZE;
}

int cuckooH2(int key) {
    return (key / TABLE_SIZE) % TABLE_SIZE;
}

void initCuckooHashTable(struct CuckooHashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->keys1[i] = EMPTY_MARKER;
        ht->values1[i] = 0;
        ht->keys2[i] = EMPTY_MARKER;
        ht->values2[i] = 0;
    }
    ht->size = 0;
    ht->collisions = 0;
}

int cuckooInsertHelper(struct CuckooHashTable* ht, int key, int value, int table, int depth) {
    if (depth > MAX_ITERATIONS) {
        return -1; 
    }
    
    if (table == 0) {
        int index = cuckooH1(key);
        if (ht->keys1[index] == EMPTY_MARKER) {
            ht->keys1[index] = key;
            ht->values1[index] = value;
            return 1;
        } else {
            
            int oldKey = ht->keys1[index];
            int oldValue = ht->values1[index];
            ht->keys1[index] = key;
            ht->values1[index] = value;
            ht->collisions++;
            return cuckooInsertHelper(ht, oldKey, oldValue, 1, depth + 1);
        }
    } else {
        int index = cuckooH2(key);
        if (ht->keys2[index] == EMPTY_MARKER) {
            ht->keys2[index] = key;
            ht->values2[index] = value;
            return 1;
        } else {
            int oldKey = ht->keys2[index];
            int oldValue = ht->values2[index];
            ht->keys2[index] = key;
            ht->values2[index] = value;
            ht->collisions++;
            return cuckooInsertHelper(ht, oldKey, oldValue, 0, depth + 1);
        }
    }
}

int cuckooInsert(struct CuckooHashTable* ht, int key, int value) {
    if (ht->size >= TABLE_SIZE * 2) {
        return -1; 
    }
    
    
    int foundValue;
    if (cuckooSearch(ht, key, &foundValue)) {
        int index1 = cuckooH1(key);
        if (ht->keys1[index1] == key) {
            ht->values1[index1] = value;
        }
        int index2 = cuckooH2(key);
        if (ht->keys2[index2] == key) {
            ht->values2[index2] = value;
        }
        return 1;
    }
    
    int result = cuckooInsertHelper(ht, key, value, 0, 0);
    if (result == 1) {
        ht->size++;
    }
    return result;
}

int cuckooSearch(struct CuckooHashTable* ht, int key, int* value) {
    int index1 = cuckooH1(key);
    if (ht->keys1[index1] == key) {
        *value = ht->values1[index1];
        return 1;
    }
    
    int index2 = cuckooH2(key);
    if (ht->keys2[index2] == key) {
        *value = ht->values2[index2];
        return 1;
    }
    
    return 0;
}

int cuckooDelete(struct CuckooHashTable* ht, int key) {
    int index1 = cuckooH1(key);
    if (ht->keys1[index1] == key) {
        ht->keys1[index1] = EMPTY_MARKER;
        ht->size--;
        return 1;
    }
    
    int index2 = cuckooH2(key);
    if (ht->keys2[index2] == key) {
        ht->keys2[index2] = EMPTY_MARKER;
        ht->size--;
        return 1;
    }
    
    return 0;
}

double calculateCuckooLoadFactor(struct CuckooHashTable* ht) {
    return (double)ht->size / (TABLE_SIZE * 2);
}

void printCuckooHashTable(struct CuckooHashTable* ht) {
    cout << "Таблица хеширования кукушки 1:" << endl;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->keys1[i] != EMPTY_MARKER) {
            cout << "Индекс " << i << ": Ключ=" << ht->keys1[i] 
                 << ", Значение=" << ht->values1[i] << endl;
        }
    }
    
    cout << "Таблица хеширования кукушки 2:" << endl;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->keys2[i] != EMPTY_MARKER) {
            cout << "Индекс " << i << ": Ключ=" << ht->keys2[i] 
                 << ", Значение=" << ht->values2[i] << endl;
        }
    }
    cout << "Коэффициент заполнения: " << calculateCuckooLoadFactor(ht) << endl;
    cout << "Коллизии: " << ht->collisions << endl;}
