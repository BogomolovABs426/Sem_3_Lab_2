#include "HashSet.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void processFile(HashSet& set, const string& filename, const string& command, const string& key) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл '" << filename << "'" << endl;
        return;
    }
    
    string line;
    cout << "Загружаем данные из файла" << endl;
    
    while (getline(file, line)) {
        if (!line.empty()) {
            set.SETADD(line);
        }
    }
    file.close();
    
    
    if (!command.empty()) {
        cout << "Выполняем запрос '" << command << "'";
        if (!key.empty()) {
            cout << " " << key;
        }
        cout << "..." << endl;
        
        if (command == "SETADD" || command == "SETDEL" || command == "SET_AT") {
            if (key.empty()) {
                cout << "Ошибка: для команды '" << command << "' требуется значение" << endl;
            } else {
                processCommand(set, command, key);
            }
        } else {
            cout << "Неизвестная команда: " << command << endl;
        }
    }
}

void printAllElements(const HashSet& set) {
    cout << "Элементы множества (" << set.count << "): {";
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
    cout << "}" << endl;
}

void interactiveMode(HashSet& set) {
    cout << "Доступные команды:" << endl;
    cout << "  SETADD <элемент> - добавить элемент" << endl;
    cout << "  SETDEL <элемент> - удалить элемент" << endl;
    cout << "  SET_AT <элемент> - проверить наличие элемента" << endl;
    cout << "  print - вывести все элементы" << endl;
    cout << "  count - показать количество элементов" << endl;
    cout << "  exit - выход" << endl;
    
    string input;
    while (true) {
        cout << "> ";
        getline(cin, input);
        
        if (input == "exit") {
            break;
        } else if (input == "print") {
            printAllElements(set);
        } else if (input == "count") {
            cout << "Количество элементов: " << set.count << endl;
        } else {
            stringstream ss(input);
            string command, key;
            ss >> command >> key;
            
            if (!key.empty()) {
                processCommand(set, command, key);
            } else if (command == "SETADD" || command == "SETDEL" || command == "SET_AT") {
                cout << "Ошибка: для команды '" << command << "' требуется аргумент" << endl;
            } else {
                cout << "Неизвестная команда: " << command << endl;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    HashSet set;
    
    string filename, command, key;
    
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        } else if (arg == "--query" && i + 1 < argc) {
            command = argv[++i];
            
            if (i + 1 < argc && argv[i+1][0] != '-') {
                key = argv[++i];
            }
        }
    }
    
    if (!filename.empty()) {
        processFile(set, filename, command, key);
    } else {
        cout << "=== АТД Множество ===" << endl;
        cout << "Использование: " << argv[0] << " --file <файл> --query <команда> [значение]" << endl;
        cout << "Пример: " << argv[0] << " --file data.txt --query SETADD 1" << endl;
    }
    
    interactiveMode(set);
    
    cout << "Выход из программы." << endl;
    return 0;
}
