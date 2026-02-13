#include "HashTable.h"
#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <random>
#include <chrono>

using namespace std;

void processAnalyzeHashing() {
    int N, M;
    cout << "Введите количество элементов для вставки (N): ";
    cin >> N;
    cout << "Введите количество поисков (M): ";
    cin >> M;
    cin.ignore();

    if (N > TABLE_SIZE) {
        cout << "Ошибка: N не может быть больше " << TABLE_SIZE << endl;
        return;
    }
    if (M <= 0) {
        cout << "Ошибка: M должно быть положительным." << endl;
        return;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);

    struct DoubleHashTable dhTable;
    initDoubleHashTable(&dhTable);

    cout << "\nТестирование двойного хеширования" << endl;

    auto start = chrono::high_resolution_clock::now();

    
    for (int i = 0; i < N; i++) {
        int key = dis(gen);
        string value = to_string(i + 1);  
        doubleHashInsert(&dhTable, key, value);
    }

    
    for (int i = 0; i < M; i++) {
        int key = dis(gen);
        string result;  
        doubleHashSearch(&dhTable, key, result);
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Время выполнения (двойное хеширование): " << duration << " мкс" << endl;
    cout << "Коэффициент заполнения: " << calculateLoadFactor(&dhTable) << endl;
    cout << "Коллизии: " << dhTable.collisions << endl;

    struct CuckooHashTable cuckooTable;
    initCuckooHashTable(&cuckooTable);

    cout << "\nТестирование хеширования кукушки" << endl;

    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        int key = dis(gen);
        int value = i + 1;
        cuckooInsert(&cuckooTable, key, value);
    }

    for (int i = 0; i < M; i++) {
        int key = dis(gen);
        int dummy;
        cuckooSearch(&cuckooTable, key, &dummy);
    }

    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Время выполнения (хеширование кукушки): " << duration << " мкс" << endl;
    cout << "Коэффициент заполнения: " << calculateCuckooLoadFactor(&cuckooTable) << endl;
    cout << "Коллизии: " << cuckooTable.collisions << endl;
} 

void processDoubleHashing() {
    struct DoubleHashTable dhTable;  
    initDoubleHashTable(&dhTable);
    
    cout << "\n=== ДВОЙНОЕ ХЕШИРОВАНИЕ ===" << endl;
    cout << "Доступные команды:" << endl;
    cout << "ADD <ключ> <значение>  - добавить элемент" << endl;
    cout << "FIND <ключ> - найти элемент" << endl;
    cout << "DEL <ключ> - удалить элемент" << endl;
    cout << "SHOW - показать таблицу" << endl;
    cout << "STATS - статистика" << endl;
    cout << "BACK - вернуться" << endl;
    
    string command;
    while (true) {
        cout << "\ndouble> ";
        getline(cin, command);
        
        if (command.empty()) continue;
        
        stringstream ss(command);
        string cmd;
        ss >> cmd;
        
        if (cmd == "ADD") {
            int key;
            string value;  

            if (ss >> key >> value) {
                cout << "h1(" << key << ") = " << (key % TABLE_SIZE) << endl;
                cout << "h2(" << key << ") = " << (1 + (key % (TABLE_SIZE - 1))) << endl;
                
                int result = doubleHashInsert(&dhTable, key, value);
                if (result == 1) {
                    cout << "Успешно добавлено." << endl;
                } else {
                    cout << "Ошибка: таблица переполнена." << endl;
                }
            } else {
                cout << "Ошибка: используйте ADD <ключ> <значение>" << endl;
            }
        }
        else if (cmd == "FIND") {
            int key;
            if (ss >> key) {
                cout << "Поиск ключа: " << key << endl;
                cout << "Проверяемые позиции: " << (key % TABLE_SIZE);
                cout << ", " << (1 + (key % (TABLE_SIZE - 1))) << endl;
                
                string value;  

                if (doubleHashSearch(&dhTable, key, value)) {  
                    cout << "Найдено: ключ=" << key << ", значение=" << value << endl;
                } else {
                    cout << "Ключ не найден." << endl;
                }
            } else {
                cout << "Ошибка: используйте FIND <ключ>" << endl;
            }
        } else if (cmd == "DEL") {
            int key;
            if (ss >> key) {
                if (doubleHashDelete(&dhTable, key)) {  
                    cout << "Ключ удален." << endl;
                } else {
                    cout << "Ключ не найден." << endl;
                }
            } else {
                cout << "Ошибка: используйте DEL <ключ>" << endl;
            }
        } else if (cmd == "SHOW") {
            printDoubleHashTable(&dhTable);

        } else if (cmd == "STATS") {
            cout << "Коэффициент заполнения: " << calculateLoadFactor(&dhTable) << endl;  
	    cout << "Коллизии: " << dhTable.collisions << endl;  
            cout << "Размер: " << dhTable.size << "/" << TABLE_SIZE << endl;  
        } else if (cmd == "BACK") {
            cout << "Выход из режима двойного хеширования." << endl;
            break;
        } else {
            cout << "Неизвестная команда." << endl;
        }
    }
}

void processCuckooHashing() {
    struct CuckooHashTable cuckooTable;
    initCuckooHashTable(&cuckooTable);
    
    cout << "\n=== ХЕШИРОВАНИЕ КУКУШКОЙ ===" << endl;
    cout << "Доступные команды:" << endl;
    cout << "ADD <ключ> <значение>  - добавить элемент" << endl;
    cout << "FIND <ключ> - найти элемент" << endl;
    cout << "DEL <ключ> - удалить элемент" << endl;
    cout << "SHOW - показать таблицу" << endl;
    cout << "STATS - статистика" << endl;
    cout << "BACK - вернуться" << endl;
    
    string command;
    while (true) {
        cout << "\ncuckoo> ";
        getline(cin, command);
        
        if (command.empty()) continue;
        
        stringstream ss(command);
        string cmd;
        ss >> cmd;
        
        if (cmd == "ADD") {
            int key, value;
            if (ss >> key >> value) {
                cout << "Таблица 1: h1(" << key << ") = " << (key % TABLE_SIZE) << endl;
                cout << "Таблица 2: h2(" << key << ") = " << ((key / TABLE_SIZE) % TABLE_SIZE) << endl;
                
                int result = cuckooInsert(&cuckooTable, key, value);
                if (result == 1) {
                    cout << "Успешно добавлено." << endl;
                } else {
                    cout << "Ошибка: бесконечный цикл вытеснений." << endl;
                }
            } else {
                cout << "Ошибка: используйте ADD <ключ> <значение>" << endl;
            }
        }
        else if (cmd == "FIND") {
            int key;
            if (ss >> key) {
                cout << "Таблица 1: позиция " << (key % TABLE_SIZE) << endl;
                cout << "Таблица 2: позиция " << ((key / TABLE_SIZE) % TABLE_SIZE) << endl;
                
                int value;
                if (cuckooSearch(&cuckooTable, key, &value)) {
                    cout << "Найдено: ключ = " << key << ", значение = " << value << endl;
                } else {
                    cout << "Ключ не найден." << endl;
                }
            } else {
                cout << "Ошибка: используйте FIND <ключ>" << endl;
            }
        }
        else if (cmd == "DEL") {
            int key;
            if (ss >> key) {
                cout << "Удаление ключа: " << key << endl;
                if (cuckooDelete(&cuckooTable, key)) {
                    cout << "Ключ удален." << endl;
                } else {
                    cout << "Ключ не найден." << endl;
                }
            } else {
                cout << "Ошибка: используйте DEL <ключ>" << endl;
            }
        }
        else if (cmd == "SHOW") {
            printCuckooHashTable(&cuckooTable);
        }
        else if (cmd == "STATS") {
            cout << "Коэффициент заполнения: " << calculateCuckooLoadFactor(&cuckooTable) << endl;
            cout << "Коллизии: " << cuckooTable.collisions << endl;
            cout << "Размер: " << cuckooTable.size << "/" << (TABLE_SIZE * 2) << endl;
        }
        else if (cmd == "BACK") {
            cout << "Выход из режима хеширования кукушки." << endl;
            break;
        }
        else {
            cout << "Неизвестная команда." << endl;
        }
    }
}

void showHelp() {
    cout << "Доступные команды в главном меню:" << endl;
    cout << "  1, double - Режим двойного хеширования" << endl;
    cout << "  2, cuckoo - Режим хеширования кукушки" << endl;
    cout << "  3, analyze - Эмпирический анализ производительности" << endl;
    cout << "  4, help - Показать справку" << endl;
    cout << "  5, exit - Выход из программы" << endl;
    cout << "\nВ каждом режиме доступны команды:" << endl;
    cout << "  ADD, FIND, DEL, SHOW, STATS, BACK" << endl;
}

int main() {
    string command;
    while (true) {
        cout << "\nmain> ";
        getline(cin, command);
        
        if (command.empty()) continue;
        
        if (command == "double") {
            processDoubleHashing();
        }
        else if (command == "cuckoo") {
            processCuckooHashing();
       
        }
	
	else if (command == "analyze") {
            processAnalyzeHashing();

        }

        else if (command == "help") {
            showHelp();
        }
        else if (command == "exit") {
            cout << "Выход из программы" << endl;
            break;
        }
        else {
            cout << "Неизвестная команда. Введите 'help' для справки." << endl;
        }
    }
    
    return 0;
}
