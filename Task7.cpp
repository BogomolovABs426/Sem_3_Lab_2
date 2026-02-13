#include "LFU.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    int capacity;
    cout << "Введите ёмкость кэша: ";
    cin >> capacity;
    cin.ignore();

    struct LFUCache cache;
    initLFUCache(&cache, capacity);

    cout << "Введите команды:\n";
    string line;
    ostringstream output;

    while (getline(cin, line)) {
        if (line.empty()) break;

        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "SET") {
            int key, value;
            if (iss >> key >> value) {
                lfuSet(&cache, key, value);
            }
        } else if (cmd == "GET") {
            int key;
            if (iss >> key) {
                int result = lfuGet(&cache, key);
                output << result << " ";
            }
        }
    }

    string res = output.str();
    if (!res.empty()) res.pop_back();
    cout << res << endl;

    return 0;
}
