#include "../include/binaryTree.h"
#include <queue>
#include <iostream>
using namespace std;

//Node构造函数实现（注意作用域！）
BinaryTree::Node::Node(int x) : val(x), left(nullptr), right(nullptr) {}

//类构造函数
BinaryTree::BinaryTree() : root(nullptr) {}

//输入一个数组构造一棵二叉树
void BinaryTree::buildBinaryTree(vector<int>& values) {
    if (values.empty()) return;

    root = new Node(values[0]);
    queue<Node*> q;
    q.push(root);
    size_t i = 1;

    while (!q.empty() && i < values.size()) {
        Node* cur = q.front(); q.pop();
        //-1表示当前节点为空
        //先左子树
        if (values[i] != -1) {
            cur->left = new Node(values[i]);
            q.push(cur->left);
        }
        i++;

        //后右子树
        if (i < values.size() && values[i] != -1) {
            cur->right = new Node(values[i]);
            q.push(cur->right);
        }
        i++;
    }
}

//二叉树的层序遍历
vector<vector<int>> BinaryTree::levelOrder() {

    //存储返回的结果，数组的每行表示二叉树的一层
    vector<vector<int>> res;
    if (!root) return res;

    //存储叶子节点的队列
    queue<Node*> q;
    q.push(root);

    //根节点在第一层
    int depth = 1;

    while (!q.empty()) {

        //当前层中叶子节点的数量
        int sz = q.size();

        //存储当前层中所有的叶子节点
        vector<int> level;

        for (int i = 0; i < sz; i++) {
            //出队列
            Node* node = q.front(); q.pop();
            cout << "depth = " << depth << " " << node->val << endl;
            level.push_back(node->val);

            //将当前叶子结点下一层的左右子树入队列
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        //一层遍历完后，压入结果数组
        res.push_back(level);
        //层数加一
        depth++;
    }

    return res;
}

//二叉树的递归遍历
void BinaryTree::traverse(Node* root) {
    if (!root) return;
    //前序遍历
    cout << root->val << endl;
    traverse(root->left);
    //中序遍历
    // cout << root->val << endl;
    traverse(root->right);
    //后序遍历
    // cout << root->val << endl;
}

void BinaryTree::traverse() {
    traverse(root); // 调用私有递归方法
}

//返回二叉树结点数目
int BinaryTree::countInside(Node* root) {
    //base case
    if (!root) return 0;

    //计算左子树节点数目
    int leftreeNum = countInside(root->left);

    //计算右子树节点数目
    int rightreeNum = countInside(root->right);

    return leftreeNum + rightreeNum + 1;
}

int BinaryTree::count() {
    return countInside(root);
}