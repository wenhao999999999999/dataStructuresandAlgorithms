#include "../include/binaryTree.h"
#include <iostream>
using namespace std;

int main() {
    BinaryTree tree;
    vector<int> values = {1, 2, 3, -1, 5, -1, 4};
    tree.buildBinaryTree(values);
    tree.levelOrder();
    return 0;
}
