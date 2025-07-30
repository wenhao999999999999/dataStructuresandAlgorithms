// 二叉树经典习题
# include<bits/stdc++.h>
using namespace std;

 struct TreeNode {
     int val;
     TreeNode *left;    
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 1.二叉树的所有路径
// 给你一个二叉树的根节点 root ，按 任意顺序 ，返回所有从根节点到叶子节点的路径。叶子节点 是指没有子节点的节点。
class Solution {
private:
    // 记录当前二叉树路径
    vector<string> path;

    // 记录所有二叉树路径
    vector<string> res;
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if (!root) return{};
        traverse(root);
        return res;
    }

    // 递归遍历函数
    void traverse (TreeNode* root) {
        // base case
        if (!root) return;

        // 判断当前路径是否走到叶子结点
        if (root->left == nullptr && root->right == nullptr) {
            // 先压入当前结点
            path.push_back(to_string(root->val));
            // 再把当前路径压入结果中
            res.push_back(joinPath(path));
            // 注意这里要撤销选择
            path.pop_back();
            return;
        }

        // 前序位置，将字符压入当前路径
        path.push_back(to_string(root->val));

        // 递归遍历左子树
        traverse(root->left);
        // 递归遍历右子树
        traverse(root->right);

        // 后序位置，撤销选择
        path.pop_back();
    }

    // 规范格式函数
    string joinPath (const vector<string> path) {
        // 字符串流
        stringstream ss;

        // 遍历字符串，合并路径
        for (int i = 0; i < path.size(); i++) {
            ss << path[i];
            if (i < path.size() -1 ) ss << "->";
        }

        return ss.str();
    } 
};

// 2.求根节点到叶节点数字之和
class Solution {
private:
    // 存放路径元素
    vector<int> path;

    // 存放每条路径的和
    vector<int> sum;

    // 返回结果
    int res;
public:
    int sumNumbers(TreeNode* root) {
        if (!root) return 0;
        traverse(root);
        for (auto n : sum) {
            res += n;
        }
        return res;
        
    }

    // 递归遍历，结合回溯算法
    void traverse(TreeNode* root) {
        // 注意：这里要结点为空直接返回
        if (!root) return;
        // base case
        if (root->left == nullptr && root->right == nullptr) {
            path.push_back(root->val);
            sum.push_back(calculateSum(path));
            path.pop_back();
            return;
        }

        // 前序位置
        path.push_back(root->val);

        // 递归遍历左右子树
        traverse(root->left);
        traverse(root->right);

        // 后序位置
        path.pop_back();

    }

    // 计算每条路径上结点的数并返回
    int calculateSum(vector<int> path) {
        int nums = 0;
        for (auto num : path) {
            nums = nums*10+num;
        }

        return nums;
    }
};

// 3.二叉树的右视图
//  给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
// BFS解法：结果数组中保存每一层结点的第一个结点的值（从右往左遍历）
class Solution {
private:
    // 存储结果数组
    vector<int> res = {};
    
    // 队列：存储每一层结点
    queue<TreeNode*> q;
public:
    vector<int> rightSideView(TreeNode* root) {
        if (root == nullptr) return res;

        q.push(root);

        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                TreeNode* curNode = q.front();
                q.pop();
                // 只保存每一层第一个结点的值
                if (i == 0) res.push_back(curNode->val);

                // 将当前节点的左右子树加入队列
                // 先压入右子树，后压入左子树
                if (curNode->right) q.push(curNode->right);
                if (curNode->left) q.push(curNode->left);
            }
        }

        return res;
    }
};

// 4.从叶节点开始的最小字符串
// 给定一颗根结点为 root 的二叉树，树中的每一个结点都有一个 [0, 25] 范围内的值，分别代表字母 'a' 到 'z'。返回 按字典序最小 的字符串，该字符串从这棵树的一个叶结点开始，到根结点结束。