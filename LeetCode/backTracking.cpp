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

// 3.封闭岛屿的数量
// 给你一个 m x n 的二进制矩阵 grid ，其中 0 代表陆地，1 代表水域。
// 岛屿是由四面相连的陆地单元格（即上下左右）组成的封闭区域。
// 封闭岛屿是完全被水域包围的岛屿（即岛屿的所有边界都被水域包围）。
// 请你返回 封闭岛屿 的 数目 。
class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        // 获取矩阵的行数和列数
        int m = grid.size();
        int n = grid[0].size();

        // 先把边界上的陆地都淹没掉
        for (int i = 0; i < m; i++) {
            // 注意这边要用递归把所有和边界相连的陆地都淹没掉
            dp(grid, i, 0); // 左边界
            dp(grid, i, n-1); // 右边界
        }

        for (int j = 0; j < n; j++) {
            dp(grid, 0, j); // 上边界
            dp(grid, m-1, j); // 下边界
        }

        int res = 0;

        // 遍历grid,剩下的岛屿都是封闭岛屿
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    // 如果当前位置是陆地且未访问过
                    res++; // 增加封闭岛屿数量

                    // 深度优先搜索，淹没所有相连的陆地
                    dp(grid, i, j);
                }
            }
        }

        return res;
    }

    // 从 (i, j) 开始，将与之相邻的陆地都变成海水
    void dp(vector<vector<int>>& grid, int i, int j) {
        // 非法索引检查
        if (i < 0 || j < 0 ||
            i >= grid.size() || j >= grid[0].size()) {
                return;
        }

        // 如果当前位置是水域，直接返回
        if (grid[i][j] == 1) {
            return;
        }

        // 将当前位置变成水域
        grid[i][j] = 1;

        // 淹没上下左右的陆地
        dp(grid,i-1, j); // 上
        dp(grid,i+1, j); // 下
        dp(grid,i, j-1); // 左
        dp(grid,i, j+1); // 右

    }
};

// 4.岛屿的最大面积
// 给你一个 m x n 的二进制矩阵 grid ，其中 0 代表水域，1 代表陆地。
// 岛屿是由四面相连的陆地单元格（即上下左右）组成的封闭区域。
// 请你计算并返回该岛屿的最大面积。如果没有岛屿，则返回 0 。
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;

        for(int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    // 如果当前位置是陆地，计算岛屿面积
                    res = max(res, dp(grid, i, j));
                }
            }
        }
        return res;
    }

    // dp 函数定义，输入：当前坐标 (i, j)，返回以 (i, j) 为起点的岛屿面积
    int dp(vector<vector<int>>& grid, int i, int j) {
        // 非法索引检查
        if (i < 0 || j < 0 ||
            i >= grid.size() || j >= grid[0].size()) {
                return 0; // 如果越界，返回面积为 0
        }

        // 如果当前位置是水域，直接返回面积为 0
        if (grid[i][j] == 0) {
            return 0;
        }

        // 将当前位置变成水域，避免重复计算
        grid[i][j] = 0;

        // 计算当前岛屿面积
        return 1 + dp(grid, i-1, j) + dp(grid, i+1, j) +
               dp(grid, i, j-1) + dp(grid, i, j+1);
    }
};

// 5.子岛屿的数量
// 给你一个 m x n 的二进制矩阵 grid1 和 grid2 ，其中 0 代表水域，1 代表陆地。
// 请你返回 grid2 中 子岛屿 的 数目 。子岛屿是指在 grid2 中的一个岛屿，且这个岛屿在 grid1 中也是一个岛屿。
// 换句话说，子岛屿是指在 grid2 中的一个岛屿，且这个岛屿在 grid1 中也是一个岛屿。
// 请你返回 grid2 中 子岛屿 的 数目 。
class Solution {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int m = grid1.size();
        int n = grid1[0].size();


        // 遍历grid1和grid2，找到所有的子岛屿
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // 如果grid2中的位置是陆地且grid1中是海水
                if (grid2[i][j] == 1 && grid1[i][j] == 0) {
                    // 进行深度优先搜索，淹没所有相连的陆地
                    dp(grid2, i, j);
                }
            }
        }
        // 现在 grid2 中的陆地已经被淹没，剩下的陆地都是子岛屿
        int res = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid2[i][j] == 1) {
                    res++;
                    // 进行深度优先搜索，淹没所有相连的陆地
                    dp(grid2, i, j);
                }
            }
        }

        return res;

    }

    // 从 (i, j) 开始，将与之相邻的陆地都变成海水
    void dp(vector<vector<int>>& grid, int i, int j) {
        // 非法索引检查
        if (i < 0 || j < 0 ||
            i >= grid.size() || j >= grid[0].size()) {
                return;
        }

        // 如果当前位置是水域，直接返回
        if (grid[i][j] == 0) {
            return;
        }

        // 将当前位置变成水域
        grid[i][j] = 0;

        // 淹没上下左右的陆地
        dp(grid, i-1, j); // 上
        dp(grid, i+1, j); // 下
        dp(grid, i, j-1); // 左
        dp(grid, i, j+1); // 右
    }
};