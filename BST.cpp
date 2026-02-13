#include "BST.h"
#include <vector>

using namespace std;

void ClearTree(TNode* node) {
    if (!node) return;
    ClearTree(node->left);
    ClearTree(node->right);
    delete node;
}

TNode* AddBST(TNode* node, int value) {
    if (!node) {
        return new TNode(value);
    }
    
    if (value < node->data) {
        node->left = AddBST(node->left, value);
    } else if (value > node->data) {
        node->right = AddBST(node->right, value);
    }
    
    return node;
}

void TADD(Tree& tree, int value, bool silent) {
    tree.root = AddBST(tree.root, value);
    tree.size++;
    
    if (!silent) {
        cout << "Элемент '" << value << "' добавлен в дерево" << endl;
    }
}

void CollectLeavesInOrder(TNode* node, vector<int>& leaves) {
    if (!node) return;
    
    CollectLeavesInOrder(node->left, leaves);
    
    if (!node->left && !node->right) {
        leaves.push_back(node->data);
    }
    
    CollectLeavesInOrder(node->right, leaves);
}

void TPRINT_LEAVES(const Tree& tree) {
    if (!tree.root) {
        cout << "Дерево пусто!" << endl;
        return;
    }
    
    vector<int> leaves;
    CollectLeavesInOrder(tree.root, leaves);
    
    for (size_t i = 0; i < leaves.size(); i++) {
        cout << leaves[i];
        if (i < leaves.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

void TCLEAR(Tree& tree) {
    ClearTree(tree.root);
    tree.root = nullptr;
    tree.size = 0;
}
