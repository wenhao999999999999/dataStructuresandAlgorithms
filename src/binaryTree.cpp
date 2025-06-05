#include "../include/binaryTree.h"
#include <queue>
#include <iostream>
using namespace std;

//Node构造函数实现（注意作用域！）
BinaryTree::Node::Node(int x) : val(x), left(nullptr), right(nullptr) {}

//类构造函数
BinaryTree::BinaryTree() : root(nullptr) {}

void BinaryTree::buildBinaryTree(vector<int>& values) {
    if (values.empty()) return;

    root = new Node(values[0]);
    queue<Node*> q;
    q.push(root);
    size_t i = 1;

    while (!q.empty() && i < values.size()) {
        Node* cur = q.front(); q.pop();

        if (values[i] != -1) {
            cur->left = new Node(values[i]);
            q.push(cur->left);
        }
        i++;

        if (i < values.size() && values[i] != -1) {
            cur->right = new Node(values[i]);
            q.push(cur->right);
        }
        i++;
    }
}

vector<vector<int>> BinaryTree::levelOrder() {
    vector<vector<int>> res;
    if (!root) return res;

    queue<Node*> q;
    q.push(root);
    int depth = 1;

    while (!q.empty()) {
        int sz = q.size();
        vector<int> level;
        for (int i = 0; i < sz; i++) {
            Node* node = q.front(); q.pop();
            cout << "depth = " << depth << " " << node->val << endl;
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        res.push_back(level);
        depth++;
    }

    return res;
}
