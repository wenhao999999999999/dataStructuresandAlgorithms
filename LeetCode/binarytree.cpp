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

// 递归遍历解法
class Solution {
private:
    // 存储当前路径
    string path;
    // 存储最短字符串
    string res;    
public:
    string smallestFromLeaf(TreeNode* root) {
        traverse(root);
        return res;
    }

    // 递归遍历函数
    void traverse (TreeNode* root) {
        if (!root) return;

        // base case
        if (root->left == nullptr && root->right == nullptr) {
            // 前序位置，压入元素
            path.push_back('a' + root->val);

            // 反转字符串
            reverse(path.begin(), path.end());

            // 第一次遍历或者当前路径字符串更小
            if (res.empty() || res > path) {
                res = path;
            }

            // 注意：恢复，正确维护 path 中的元素
            reverse(path.begin(), path.end());

            // 注意：后序位置，撤销选择
            path.pop_back();
            return;
        }

        // 前序位置
        path.push_back('a' + root->val);

        // 递归遍历左右子树
        traverse(root->left);
        traverse(root->right);

        // 注意：后序位置，撤销选择
        path.pop_back();
    }
};

// 5.从根到叶的二进制数之和
// 给出一棵二叉树，其上每个结点的值都是 0 或 1 。每一条从根到叶的路径都代表一个从最高有效位开始的二进制数。对树上的每一片叶子，我们都要找出从根到该叶子的路径所表示的数字。

// DFS解法：首先求出每一条路径，接着将每一条路径转换为十进制数，最后求和
class Solution {
private:
    // 存储当前路径的结点
    vector<TreeNode*> path;

    // 存储结果
    int sum = 0;

    // 存储所有路径的十进制数
    vector<int> nums;
public:
    // 主函数入口 
    int sumRootToLeaf(TreeNode* root) {
        traverse(root);
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        return sum;
    }

    // DFS
    void traverse(TreeNode* root) {
        // 判断当前节点是否为空
        if (root == nullptr) return;

        // base case
        if (root->left == nullptr && root->right == nullptr) {
            // 前序位置，压入结点
            path.push_back(root);

            // 将当前路径转换为十进制数字并保存
            nums.push_back(pathToNum(path));

            // 后序位置，弹出当前结点
            path.pop_back();
            return;
        }

        // 前序位置，压入结点
        path.push_back(root);

        // 递归遍历左右子树
        traverse(root->left);
        traverse(root->right);

        // 后序位置，弹出结点
        path.pop_back();
    }
    
    // 将每一条结点路径转换为十进制数字
    int pathToNum (vector<TreeNode*> path) {
        int num = 0;
        for (int i = 0; i < path.size(); i++) {
            // 注意：第一个结点是高位
            num += path[i]->val *  pow(2, path.size()-i-1) ; 
        }
        return num;
    }
};