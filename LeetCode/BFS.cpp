// BFS (Breadth-First Search) 算法解题套路框架
#include <bits/stdc++.h>
#include "../include/binaryTree.h"

using namespace std;

// 1. 滑动谜题
class Solution {
public:
    // 计算滑动谜题从初始状态board到达目标状态所需的最小步数
    int slidingPuzzle(vector<vector<int>>& board) {
        string target = "123450";

        // 将二维数组board转换为一个字符串表示
        string start = "";
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                 start = start + to_string(board[i][j]);
            }
        }

        // 使用广度优先搜索算法来找到从start到target的最短路径
        queue<string> q;
        unordered_set<string> visited;
        q.push(start);
        visited.insert(start);

        int steps = 0;
        while(!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                string cur = q.front();
                q.pop();

                // 判断是否到达目标状态
                if (cur == target) {
                    return steps;
                }

                // 将数字0与相邻的数字交换位置，生成所有可能的邻居状态
                for (string neighborBoard : getNeighbors(cur)) {
                    if (!visited.count(neighborBoard)) {
                        q.push(neighborBoard);
                        visited.insert(neighborBoard);
                    }
                }
            }
            steps++;
        }
        return -1; // 如果无法到达目标状态，返回 -1
    }

    // 根据当前状态board生成所有可能的邻居状态
    vector<string> getNeighbors(string board) {
        // 记录一维字符串的相邻索引
        vector<vector<int>> mapping = {
            {1, 3}, // 0
            {0, 2, 4}, // 1
            {1, 5}, // 2
            {0, 4}, // 3
            {1, 3, 5}, // 4
            {2, 4} // 5
        };

        int zeroIndex = board.find('0');
        vector<string> neighbors;
        for (int adj : mapping[zeroIndex]) {
            string neighbor = board;
            swap(neighbor[zeroIndex], neighbor[adj]);
            neighbors.push_back(neighbor);
        }
        return neighbors;
    }
};     


// 2. 打开转盘锁
// 给定一个四位数的转盘锁，初始状态为 "0000"。每次可以将某一位数字加1或减1，0和9是环形的。
// 请你返回打开转盘锁所需的最少步数。每次只能改变一位数字，且只能在 "0000" 到 "9999" 的范围内。
// 列表 deadends 包含了不能到达的状态，target 是目标状态。
// 如果无法到达目标状态，返回 -1。
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        // 记录需要跳过的死亡密码
        unordered_set<string> deads(deadends.begin(), deadends.end());

        if (deads.count("0000")) {
            return -1; // 如果初始状态就是死亡密码，直接返回 -1
        }

        // 记录已经穷举过的密码，防止走回头路
        unordered_set<string> visited;
        visited.insert("0000");

        // 使用队列进行广度优先搜索
        queue<string> q;
        q.push("0000");
        
        // 记录当前步数
        int steps = 0;

        while (!q.empty()) {
            int sz = q.size();
            
            // 将当前队列中的所有节点向周围扩散
            for (int i = 0; i < sz; i++) {
                // 取出当前节点
                string cur = q.front();
                q.pop();

                // 判断是否到达终点
                if (cur == target) {
                    return steps;
                }

                // 将一个节点的合法相邻节点加入队列
                for (string neighbor : getNeihbors(cur)) {
                    if (!visited.count(neighbor) &&!deads.count(neighbor)) {
                        q.push(neighbor);
                        visited.insert(neighbor);
                    }

                }
            }

            // 步数加1
            steps++;
        }

        return -1; // 如果无法到达目标状态，返回 -1
    }

    // 根据当前状态board生成所有可能的邻居状态
    vector<string> getNeihbors(string board) {
        vector<string> neighbors;
        for (int i = 0; i < 4; i++) {
            // 尝试将第i位数字加1
            string neighbor = board;
            int digit = board[i] - '0';
            digit = (digit + 1) % 10;
            neighbor[i] = digit + '0';
            neighbors.push_back(neighbor);

            // 尝试将第 i 位数字减1
            neighbor = board;
            digit = board[i] - '0';
            digit = (digit + 9) % 10;
            neighbor[i] = digit + '0';
            neighbors.push_back(neighbor);
        }
        return neighbors;
    }
};

// 3.完全二叉树插入器
// 完全二叉树 是每一层（除最后一层外）都是完全填充（即，节点数达到最大）的，并且所有的节点都尽可能地集中在左侧。
// 设计一种算法，将一个新节点插入到一棵完全二叉树中，并在插入后保持其完整。
// 实现 CBTInserter 类:
// CBTInserter(TreeNode root) 使用头节点为 root 的给定树初始化该数据结构；
// CBTInserter.insert(int v)  向树中插入一个值为 Node.val == val的新节点 TreeNode。使树保持完全二叉树的状态，并返回插入节点 TreeNode 的父节点的值；
// CBTInserter.get_root()  返回树的头节点。

class CBTInserter {
private:
    TreeNode* root;
    queue<TreeNode*> q;
public:
    // 构造函数，初始化根节点并使用广度优先搜索找到所有可以插入子节点的位置
    CBTInserter(TreeNode* root) {
        this->root = root;

        // BFS 找到底部可插入的节点
        queue<TreeNode*> temp;
        temp.push(root);
        while (!temp.empty()) {
            TreeNode* node = temp.front();
            temp.pop();
            if (node->left) {
                temp.push(node->left);
            }
            if (node->right) {
                temp.push(node->right);
            }

            if (node->left == nullptr || node->right == nullptr) {
                // 找到完全二叉树的底部底部可以插入的节点
                q.push(node);
            }
        
        }
    }
    
    // 插入新节点到完全二叉树中，并返回插入节点的父节点值
    int insert(int v) {
        TreeNode* node = new TreeNode(v);
        TreeNode* cur = q.front();

        // 进行插入
        if (cur->left == nullptr) {
            cur->left = node;
        } else if (cur->right == nullptr) {
            cur->right = node;
            // 当且仅当插入节点是父节点的右孩子时，才需要更新父节点的值
            q.pop();
        }

        // 新节点的左右节点也是可以插入的
        q.push(node);
        return cur->val;

    }

    // 返回完全二叉树的根节点
    TreeNode* get_root() {
        return root;
    }
};