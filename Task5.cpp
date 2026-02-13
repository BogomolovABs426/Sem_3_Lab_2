#include "BST.h"
#include <sstream>

using namespace std;

int main() {
    Tree tree;
    string input;
    
    getline(cin, input);
    
    stringstream ss(input);
    int number;
    
    while (ss >> number) {
        TADD(tree, number, true);
    }
    
    TPRINT_LEAVES(tree);
    
    TCLEAR(tree);
    return 0;
}
