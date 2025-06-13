//声明二叉树类的变量和方法
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
    int countInside(Node* root); 
public:
    //二叉树对象构造函数
    BinaryTree();

    //输入一个数组，创建一颗二叉树
    void buildBinaryTree(vector<int>& values);

    //二叉树的层序遍历
    vector<vector<int>> levelOrder();

    //二叉树的递归遍历
    void traverse();

    //返回二叉树结点数目
    int count();
    
};

#endif // BINARY_TREE_H
