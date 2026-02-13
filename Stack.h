#ifndef STACK_H
#define STACK_H

struct Node {
    int data;
    Node* next;
    
    Node(int value);
};

struct Stack {
    Node* top;
    int size;

    Stack();
    bool isEmpty();
    void push(int value);
    int pop();
    int getSize();
    ~Stack();
};

#endif
