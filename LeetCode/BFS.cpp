// BFS (Breadth-First Search) 算法解题套路框架
#include <bits/stdc++.h>

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
        // 初始编码
    }
};