#include "Stack.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int performOperation(int a, int b, const string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) {
            throw runtime_error("Деление на ноль!");
        }
        return a / b;
    }
    throw runtime_error("Неизвестный оператор: " + op);
}

int evaluateRPN(const string& expression) {
    Stack stack;
    stringstream ss(expression);
    string token;
    
    while (ss >> token) {
        if (isOperator(token)) {
            if (stack.getSize() < 2) {
                throw runtime_error("Недостаточно операндов для оператора: " + token);
            }
            int b = stack.pop();
            int a = stack.pop();
            int result = performOperation(a, b, token);
            stack.push(result);
        } else {
            try {
                int number = stoi(token);
                stack.push(number);
            } catch (const invalid_argument& e) {
                throw runtime_error("Неверный токен: " + token);
            }
        }
    }
    
    if (stack.getSize() != 1) {
        throw runtime_error("Неверное выражение: слишком много операндов");
    }
    
    return stack.pop();
}

int main() {
    string input;
    cout << "> ";
    getline(cin, input);
    
    if (!input.empty()) {
        try {
            int result = evaluateRPN(input);
            cout << "Результат: " << result << endl;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
    
    return 0;
}
