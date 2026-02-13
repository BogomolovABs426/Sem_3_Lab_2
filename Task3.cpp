#include "HashSet.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int countCommonElements(const HashSet& set1, const HashSet& set2) {
    int commonCount = 0;
    
    for (int i = 0; i < HashSet::TABLE_SIZE; i++) {
        HashNode* current = set1.table[i];
        while (current != nullptr) {
            if (set2.SET_AT(current->key)) {
                commonCount++;
            }
            current = current->next;
        }
    }
    
    return commonCount;
}

void printSet(const HashSet& set) {
    cout << "{";
    bool first = true;
    for (int i = 0; i < HashSet::TABLE_SIZE; i++) {
        HashNode* current = set.table[i];
        while (current != nullptr) {
            if (!first) cout << ", ";
            cout << current->key;
            first = false;
            current = current->next;
        }
    }
    cout << "}";
}

vector<HashSet> ParseSetsInput(const string& input) {
    vector<HashSet> sets;
    string cleaned = input;
    
    
    if (cleaned.front() == '{' && cleaned.back() == '}') {
        cleaned = cleaned.substr(1, cleaned.length() - 2);
    }
    
    stringstream ss(cleaned);
    string setStr;
    int braceCount = 0;
    string currentSet = "";
    
    for (char c : cleaned) {
        if (c == '{') {
            braceCount++;
            if (braceCount == 1) {
                currentSet = "";
                continue;
            }
        }
        if (c == '}') {
            braceCount--;
            if (braceCount == 0) {
                HashSet set;
                stringstream setStream(currentSet);
                string number;
                 
                while (getline(setStream, number, ',')) {
                    number.erase(remove_if(number.begin(), number.end(), ::isspace), number.end());
                    if (!number.empty()) {
                        set.SETADD(number);
                    }
                }
                sets.push_back(set);
                currentSet = "";
                continue;
            }
        }
        if (braceCount > 0) {
            currentSet += c;
        }
    }
    
    return sets;
}

int main() {
    vector<HashSet> sets;
    string input;
    cout << "Ввод: ";
    getline(cin, input);
    
    if (input.empty()) {
        cout << "Ошибка: пустой ввод!" << endl;
        return 1;
    }
    
    sets = ParseSetsInput(input);
    
    if (sets.size() < 2) {
        cout << "Ошибка: нужно ввести хотя бы 2 множества!" << endl;
        return 1;
    }
    
    
    int maxCommon = 0;
    int set1Index = -1, set2Index = -1;
    
    for (int i = 0; i < sets.size(); i++) {
        for (int j = i + 1; j < sets.size(); j++) {
            int common = countCommonElements(sets[i], sets[j]);            
            if (common > maxCommon) {
                maxCommon = common;
                set1Index = i;
                set2Index = j;
            }
        }
    }
    
    if (maxCommon > 0) {
        cout << "Пара множеств с максимальным количеством общих элементов:" << endl;
        cout << "Множество " << (set1Index + 1) << ": ";
        printSet(sets[set1Index]);
        cout << endl;
        
        cout << "Множество " << (set2Index + 1) << ": ";
        printSet(sets[set2Index]);
        cout << endl;
        
        cout << "Количество общих элементов: " << maxCommon << endl;
        
        cout << "Общие элементы: {";
        bool first = true;
        for (int i = 0; i < HashSet::TABLE_SIZE; i++) {
            HashNode* current = sets[set1Index].table[i];
            while (current != nullptr) {
                if (sets[set2Index].SET_AT(current->key)) {
                    if (!first) cout << ", ";
                    cout << current->key;
                    first = false;
                }
                current = current->next;
            }
        }
        cout << "}" << endl;
    } else {
        cout << "Нет пар множеств с общими элементами" << endl;
    }
    
    return 0;
}
