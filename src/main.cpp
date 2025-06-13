#include "../include/binaryTree.h"
#include "../include/naryTree.h"
#include <iostream>
using namespace std;

int main() {

    //实例化一个二叉树对象
    BinaryTree binaryTree;

    //创建根节点和子结点
    TreeNode* root = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* node6 = new TreeNode(6);

    //建立父子关系
    root->addChild(node2);
    root->addChild(node3);
    root->addChild(node4);

    node3->addChild(node5);
    node3->addChild(node6);

    //实例化一个多叉树对象
    NaryTree naryTree(root);

    vector<int> values = {1, 2, 3, -1, 5, -1, 4};
    binaryTree.buildBinaryTree(values);
    // binaryTree.levelOrder();
    // binaryTree.traverse();
    naryTree.traverse();
    return 0;
}
