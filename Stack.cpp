#include "Stack.h"
#include <stdexcept>

using namespace std;

// Реализация Node
Node::Node(int value) : data(value), next(nullptr) {}

// Реализация Stack
Stack::Stack() : top(nullptr), size(0) {}

bool Stack::isEmpty() {
    return top == nullptr;
}

void Stack::push(int value) {
    Node* newNode = new Node(value);
    newNode->next = top;
    top = newNode;
    size++;
}

int Stack::pop() {
    if (isEmpty()) {
        throw runtime_error("Стек пустой.");
    }
    
    Node* temp = top;
    int value = top->data;
    top = top->next;
    delete temp;
    size--;
    
    return value;
}

int Stack::getSize() {
    return size;
}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}
