// 回溯算法
# include <bits/stdc++.h>
using namespace std;

// 1. 全排列
class Solution {
public:
// 存储全排列
vector<vector<int>> res;

    // 主函数：输入一组不重复的数字，返回它们的全排列
    vector<vector<int>> permute(vector<int>& nums) {    
        // 记录路径
        vector<int> path;

        // 记录是否访问过
        vector<bool> visited(nums.size(), false);

        // 回溯函数
        backtrack(nums, path, visited);

        return res;
    }

    // 回溯函数：生成全排列
    // 输入：nums 数组，当前路径 path，访问标记 visited
    void backtrack(vector<int>& nums, vector<int>& path, vector<bool>& visited) {
        // base case: 路径长度等于数组长度
        if (path.size() == nums.size()) {
            // 找到一个全排列，加入结果集
            res.push_back(path);
            return;
        }

        // 遍历所有数字
        for (int i = 0; i < nums.size(); i++) {
            // 排除不合法的选择，适用于元素不可复选的情况
            if (visited[i]) continue;

            // 做选择：将当前数字加入路径
            path.push_back(nums[i]);

            // 标记为已访问
            visited[i] = true;

            // 递归调用：继续生成下一个数字
            backtrack(nums, path, visited);

            // 撤销选择：从路径中移除当前数字
            path.pop_back();
            visited[i] = false;
        }

    }
};

// 2.岛屿问题
class Solution {
public:
    // 二维矩阵遍历框架
    void dfs(vector<vector<char>>& grid, int i, int j) {
        int m = grid.size();
        int n = grid[0].size();

        // 边界条件：如果越界或已经访问过，直接返回
        if (i < 0 || j < 0 || i >= m || j >= n) return;

        // 如果当前位置是水，直接返回
        if (grid[i][j] == '0') return;

        // 将 (i, j) 变成海水
        grid[i][j] = '0';

        // 淹没上下左右的陆地
        dfs(grid, i-1, j); // 上
        dfs(grid, i+1, j); // 下
        dfs(grid, i, j-1); // 左
        dfs(grid, i, j+1); // 右

    }

    // 岛屿数量
    int numIslands(vector<vector<char>>& grid) {
        // 获取矩阵的行数和列数
        int m = grid.size();
        int n = grid[0].size();

        // 存储结果
        int res = 0;

        // 遍历 grid
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // 如果当前位置是陆地且未访问过
                if (grid[i][j] == '1') {
                    // 增加岛屿数量
                    res++;

                    // 深度优先搜索，标记所有相连的陆地
                    dfs(grid, i, j);
                }
            }
        }
        return res;
    }
};