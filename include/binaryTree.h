#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <vector>
using namespace std;

class BinaryTree {
private:
    struct Node {
        int val;
        Node* left;
        Node* right;
        Node(int x);
    };
    Node* root;
    void traverse(Node* root);
public:
    BinaryTree();
    void buildBinaryTree(vector<int>& values);
    vector<vector<int>> levelOrder();
    void traverse();
};

#endif // BINARY_TREE_H
