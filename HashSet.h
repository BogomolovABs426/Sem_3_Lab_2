#ifndef HASHSET_H
#define HASHSET_H

#include <string>

using namespace std;

struct HashNode {
    string key;
    HashNode* next;
    
    HashNode(const string& k);
};

struct HashSet {
public:
    static const int TABLE_SIZE = 1000;
    HashNode** table;
    int count;

    HashSet();
    HashSet(const HashSet& other);
    HashSet& operator=(const HashSet& other);
    void SETADD(const string& key);
    void SETDEL(const string& key);
    bool SET_AT(const string& key) const;
    
    ~HashSet();
};

unsigned int HashFunction(const string& key);

#endif
