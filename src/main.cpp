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

    //创建二叉树
    binaryTree.buildBinaryTree(values);

    //二叉树层序遍历
    // binaryTree.levelOrder();

    //二叉树递归遍历
    // binaryTree.traverse();

    //多叉树递归遍历
    // naryTree.traverse();

    //返回二叉树节点数目
    cout << binaryTree.count() << endl;
    return 0;
}
