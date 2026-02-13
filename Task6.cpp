// Task6.cpp
#include "HashTable.h"
#include <iostream>
#include <string>

using namespace std;

DoubleHashTable ht;

void initMap() {
    initDoubleHashTable(&ht);
    doubleHashInsert(&ht, 1000, "M");
    doubleHashInsert(&ht, 900,  "CM");
    doubleHashInsert(&ht, 500,  "D");
    doubleHashInsert(&ht, 400,  "CD");
    doubleHashInsert(&ht, 100,  "C");
    doubleHashInsert(&ht, 90,   "XC");
    doubleHashInsert(&ht, 50,   "L");
    doubleHashInsert(&ht, 40,   "XL");
    doubleHashInsert(&ht, 10,   "X");
    doubleHashInsert(&ht, 9,    "IX");
    doubleHashInsert(&ht, 5,    "V");
    doubleHashInsert(&ht, 4,    "IV");
    doubleHashInsert(&ht, 1,    "I");
}

void toRoman(int n) {
    const int keys[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const int numKeys = sizeof(keys) / sizeof(keys[0]);

    string result = "";

    for (int i = 0; i < numKeys; ++i) {
        int value = keys[i];
        while (n >= value) {
            std::string symbol;
            if (doubleHashSearch(&ht, value, symbol)) {
                result += symbol;
                n -= value;
            } else {
                break;
            }
        }
    }

    cout << result << endl;
}

int main() {
    initMap();
    int n;
    cin >> n;
    if (n < 1) return 1;
    toRoman(n);
    return 0;
}
