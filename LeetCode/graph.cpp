#include <bits/stdc++.h>
using namespace std;

// 图经典习题

// 1.被围绕的区域
// 给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' 组成，捕获 所有 被围绕的区域：
// 连接：一个单元格与水平或垂直方向上相邻的单元格连接。
// 区域：连接所有 'O' 的单元格来形成一个区域。
// 围绕：如果您可以用 'X' 单元格 连接这个区域，并且区域中没有任何单元格位于 board 边缘，则该区域被 'X' 单元格围绕。
// 通过 原地 将输入矩阵中的所有 'O' 替换为 'X' 来 捕获被围绕的区域。你不需要返回任何值。

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty()) return;
        int m = board.size();
        int n = board[0].size();

        // 步骤一：将边界 'O' 元素改成 'A'
        for (int i = 0; i < m; i++) {
            dfs(board, i, 0); // 左边界
            dfs(board, i, n-1); // 右边界
        }

        for (int j = 0; j < n; j++) {
            dfs(board, 0, j); // 上边界
            dfs(board, m-1, j); // 下边界
        }


        // 步骤二：将所有'O'字符改成'X'
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                } else if (board[i][j] == 'A') {
                    board[i][j] = 'O';
                }
            }
        }

        
    }

    // dfs 淹没所有与i，j相邻的元素
    void dfs(vector<vector<char>>& board, int i, int j) {
        int m = board.size();
        int n = board[0].size();
        if (i < 0 || j < 0 || i >= m || j >= n)
            return;

        if (board[i][j] == 'X')
            return;

        board[i][j] = 'A';

        dfs(board, i - 1, j);
        dfs(board, i + 1, j);
        dfs(board, i, j - 1);
        dfs(board, i, j + 1);
    }
};

// bfs 解法：步骤一：将将边界 'O' 元素加入队列并标记为 'A'；步骤二：BFS处理所有与边界相连的 'O'，标记为 'A'；步骤三：替换字符（'O'→'X'，'A'→'O'）
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty()) return;
        int m = board.size();
        int n = board[0].size();
        queue<pair<int, int>> q;

        // 步骤一：将边界 'O' 元素加入队列并标记为 'A'
        // 处理左右边界
        for (int i = 0; i < m; ++i) {
            if (board[i][0] == 'O') {
                board[i][0] = 'A';
                q.push({i, 0});
            }
            if (board[i][n-1] == 'O') {
                board[i][n-1] = 'A';
                q.push({i, n-1});
            }
        }
        // 处理上下边界（跳过已处理的角落）
        for (int j = 1; j < n-1; ++j) {
            if (board[0][j] == 'O') {
                board[0][j] = 'A';
                q.push({0, j});
            }
            if (board[m-1][j] == 'O') {
                board[m-1][j] = 'A';
                q.push({m-1, j});
            }
        }

        // 方向数组：上下左右
        vector<pair<int, int>> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        // 步骤二：BFS处理所有与边界相连的 'O'，标记为 'A'
        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();
            // 遍历四个方向
            for (auto [di, dj] : dirs) {
                int x = i + di;
                int y = j + dj;
                // 检查是否在矩阵范围内，且是未标记的 'O'
                if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'O') {
                    board[x][y] = 'A';  // 标记为 'A'
                    q.push({x, y});    // 加入队列继续处理
                }
            }
        }

        // 步骤三：替换字符（'O'→'X'，'A'→'O'）
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                } else if (board[i][j] == 'A') {
                    board[i][j] = 'O';
                }
            }
        }
    }
};

// 2.所有可能的路径
// 题目描述：给你一个有 n 个节点的 有向无环图（DAG），请你找出从节点 0 到节点 n-1 的所有路径并输出（不要求按特定顺序）
//  graph[i] 是一个从节点 i 可以访问的所有节点的列表（即从节点 i 到节点 graph[i][j]存在一条有向边）。

// 解题思路： 维护一个二维数组路径变量，存储每一条路径，层序遍历过程中，不断更新结果
class Solution {
private:
    vector<int> path;
    vector<vector<int>> res;
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int n = graph.size();
        traverse(graph, 0, n - 1);
        return res;
    }
    // dfs
    void traverse(vector<vector<int>>& graph, int src, int end) {
        
        // 前序位置
        path.push_back(src);
        
        // base case
        if (src == end) {
            res.push_back(path);
            // 注意：找到一条路径后需要将当前结点弹出，因为可能存在其他路径到达中终点
            path.pop_back();
            return;
        }

        // 层序遍历邻居节点
        for (auto node : graph[src]) {
            traverse(graph, node, end);
        }

        // 后序位置
        // 注意：到达当前结点可能存在其他路径，因此需要弹出当前结点。
        path.pop_back();

    }
};