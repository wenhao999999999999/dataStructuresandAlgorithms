#include "../include/binaryTree.h"
#include <iostream>
using namespace std;

int main() {
    BinaryTree binaryTree;
    vector<int> values = {1, 2, 3, -1, 5, -1, 4};
    binaryTree.buildBinaryTree(values);
    // binaryTree.levelOrder();
    binaryTree.traverse();
    return 0;
}
