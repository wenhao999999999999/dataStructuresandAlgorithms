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

    //二叉树根节点
    Node* root;

    //二叉树遍历到的节点的深度
    int depth = 0;

    //二叉树的最大深度
    int maxdepth = 0; 

    //二叉树的最大直径
    int maxdiameter = 0;

    //二叉树的前序遍历结果，递归思路
    vector<int> preordertraversal;

    //返回二叉树前序遍历结果，分治思路
    vector<int> preOrderTraversal(Node* root);

    void traverse(Node* root);
    int countInside(Node* root);
    int maxDepth1(Node* root);
    int maxDepth2(Node* root); 
    int diameterOfBinaryTree(Node* root);
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

    //返回二叉树的最大深度
    int maxDepth();

    //返回二叉树前序遍历结果
    vector<int> PreOrderTraversal();

    //返回二叉树的直径
    int diameterOfBinaryTree();


    
};

#endif // BINARY_TREE_H
