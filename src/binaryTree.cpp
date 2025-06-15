#include "../include/binaryTree.h"
#include <queue>
#include <iostream>
using namespace std;

//Node构造函数实现（注意作用域！）
BinaryTree::Node::Node(int x) : val(x), left(nullptr), right(nullptr) {}

//二叉树类构造函数
BinaryTree::BinaryTree() : root(nullptr) {}

//创建一棵二叉树
    //输入：数组
    //返回：无
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
    //输入：无
    //返回：二维数组
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
    //输入：无
    //返回：无
void BinaryTree::traverse(Node* root) {
    if (!root) return;
    //前序遍历
    // cout << root->val << endl;

    //前序遍历位置，进入结点，增加深度
    depth++;

    //前序遍历位置加入结点
    preordertraversal.push_back(root->val);

    //遍历到叶子结点时，记录最大深度
    if (root->left == nullptr && root->right == nullptr) {
        maxdepth = max(depth, maxdepth);
    }

    traverse(root->left);
    //中序遍历
    // cout << root->val << endl;
    traverse(root->right);
    //后序遍历
    // cout << root->val << endl;

    //后续位置，离开结点，减小深度
    depth--;
}

void BinaryTree::traverse() {
    traverse(root); // 调用私有递归方法
}

//统计二叉树结点数目，分解思路
    //输入：二叉树根节点
    //返回：二叉树节点数目
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

//返回二叉树的最大深度:分治问题的思路解法
//递归函数定义：
    //输入：二叉树根节点
    //返回：二叉树的最大深度
int BinaryTree::maxDepth1(Node* head) {
    //base case
    if (!head) return 0;

    //计算左子树的最大深度
    int lefMaxDepth = maxDepth1(head->left);

    //计算右子树的最大深度
    int righMaxDepth = maxDepth1(head->right);

    //计算并更新二叉树的最大直径
    int cur = lefMaxDepth + righMaxDepth;
    maxdiameter = max(maxdiameter, cur);

    //最大深度 = 左/右子树最大深度 + 根节点
    return max(lefMaxDepth, righMaxDepth) + 1;
}

//返回二叉树的最大深度：遍历的思路
int BinaryTree::maxDepth2(Node* root) {
    traverse(root);
    return maxdepth;
}


//返回二叉树的最大深度，外部调用
int BinaryTree::maxDepth() {
    // return maxDepth1(root);
    return maxDepth2(root);
}

//返回二叉树的前序遍历结果,分解问题思路
//递归函数的定义：
    //输入：二叉树根节点
    //返回：二叉树的前序遍历结果
vector<int> BinaryTree::preOrderTraversal(Node* root) {
    //初始化返回数组
    vector<int> res;

    //base case
    if (root == nullptr) return res;

    //根节点压入返回数组
    res.push_back(root->val);

    //左子树前序遍历结果
    vector<int> leftPre = preOrderTraversal(root->left);

    //右子树前序遍历结果
    vector<int> rightPre = preOrderTraversal(root->right);

    //合并结果
    res.insert(res.end(), leftPre.begin(), leftPre.end());
    res.insert(res.end(), rightPre.begin(), rightPre.end());

    //返回结果
    return res;
}

//返回二叉树前序遍历结果，外部调用接口
vector<int> BinaryTree::PreOrderTraversal() {
    //思路一：遍历
    // traverse(root);
    // return preordertraversal;

    //思路二：分解
    return preOrderTraversal(root);
}

//计算二叉树的直径
    //输入：二叉树根节点
    //返回：二叉树直径
int BinaryTree::diameterOfBinaryTree(Node* root) {
    maxDepth1(root);
    return maxdiameter;
}

//外部接口
int BinaryTree:: diameterOfBinaryTree() {
    return diameterOfBinaryTree(root);
}


