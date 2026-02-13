#ifndef TREE_H
#define TREE_H

#include <iostream>

struct TNode {
    int data;
    TNode* left;
    TNode* right;
    
    TNode(int val, TNode* lft = nullptr, TNode* rght = nullptr) : data(val), left(lft), right(rght) {}
};

struct Tree { 
    TNode* root = nullptr; 
    size_t size = 0; 
};

void TADD(Tree& tree, int value, bool silent = false);
void TPRINT_LEAVES(const Tree& tree);
void TCLEAR(Tree& tree);

#endif
