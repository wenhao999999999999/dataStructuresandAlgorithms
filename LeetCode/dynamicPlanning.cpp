// 动态规划解题套路框架
# include <bits/stdc++.h>
using namespace std;

// 首先，虽然动态规划的核心思想就是穷举求最值，但是问题可以千变万化，穷举所有可行解其实并不是一件容易的事，需要你熟练掌握递归思维，只有列出正确的「状态转移方程」，才能正确地穷举。
// 而且，你需要判断算法问题是否具备「最优子结构」，是否能够通过子问题的最值得到原问题的最值。
// 另外，动态规划问题存在「重叠子问题」，如果暴力穷举的话效率会很低，所以需要你使用「备忘录」或者「DP table」来优化穷举过程，避免不必要的计算。

class Solution {
public:
    // 1.零钱兑换
    // 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。
    // 计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
    vector<int> memo;

    int coinChange(vector<int>& coins, int amount) {
        // 备忘录，memo[i] 表示凑成总金额 i 做需要的最少硬币数目
       memo = vector<int> (amount+1, -666);
        return dp(coins, amount);
        
    }

    // dp函数定义：
    // 输入：硬币面额数组 coins， 总金额 amount;
    // 返回：凑成总金额所需的最少的硬币个数；
    int dp(vector<int>& coins, int amount) {
        // base case
        if (amount == 0) return 0;
        // 注意：添加总金额小于零判断
        if (amount < 0) return -1;

        if (memo[amount] != -666) return memo[amount];

        int res = INT_MAX;
        for (auto coin : coins) {
            // 计算子问题的答案
            int subproblem = dp(coins, amount - coin);
            
            // 注意：子问题无解则跳过
            if (subproblem == -1) continue;

            // 在子问题中寻找最优解，然后加一
            res = min(res, subproblem + 1);
        }
        // 注意：要判断是否有解
        memo[amount] = res == INT_MAX ? -1 : res;
        return memo[amount];
    }
};

// 2. 最长递增子序列
// 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
// 子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        // 数组的长度
        int n = nums.size();
        // dp 数组定义：dp[i] 表示以 nums[i] 这个数结尾的最长递增子序列的长度
        // 全部初始化为 1
        vector<int> dp(n, 1);

        // base case : dp 数组全部初始化为 1
        for (int i = 0; i < n; i++) {
            // nums[i] 前面的所有数都可以作为递增子序列的前缀
            // 注意：这里的 i 是从 0 开始的，所以 j 的范围是 [0, i-1]
            // 也就是 nums[i] 前面的所有数都可以作为递增子序
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
        }

        // 根据函数定义，返回值可以定义如下：
        int res = 1;
        for (int i = 0; i < dp.size(); i++) {
            res = max(res, dp[i]);
        }
        return res;
    }
 
};

// 3. 下降路径最小和
// 给你一个 n x n 的 方形 整数数组 matrix ，请你找出并返回通过 matrix 的下降路径 的 最小和 。
// 下降路径 可以从第一行中的任何元素开始，并从每一行中选择一个元素。在下一行选择的元素和当前行所选元素最多相隔一列（即位于正下方或者沿对角线向左或者向右的第一个元素）。具体来说，位置 (row, col) 的下一个元素应当是 (row + 1, col - 1)、(row + 1, col) 或者 (row + 1, col + 1) 。

class Solution {
public:
    // 备忘录
    vector<vector<int>> memo;

    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int res = INT_MAX;
        
        // 备忘录里的值初始化为 66666
        memo = vector<vector<int>>(n, vector<int>(n, 66666));

        // 终点可能回落到最后一行的任意一列
        for (int i = 0; i < n; i++) {
            res = min (res, dp(matrix, n-1, i));
        }

        return res;
    }

     // dp函数定义：从第一行（matrix[0][..]）向下落，落到位置 matrix[i][j] 的最小路径和为 dp(matrix, i, j)。
     // 输入：状态（落入的位置）
     // 返回：最小路径和
    int dp(vector<vector<int>>& matrix, int i, int j) {
        // 1.非法索引检查
        if (i < 0 || j < 0 ||
            j >= matrix.size() ||
            j >= matrix.size()) {
                return INT_MAX; // 因为我们调用的是 min 函数，最终返回的值是最小值，所以对于不合法的索引，只要 dp 函数返回一个永远不会被取到的最大值即可。
        }

        // 2.base case
        // 如何确定：回顾我们的 dp 函数定义：
        // 从第一行（matrix[0][..]）向下落，落到位置 matrix[i][j] 的最小路径和为 dp(matrix, i, j)。
        // 根据这个定义，我们就是从 matrix[0][j] 开始下落。那如果我们想落到的目的地就是 i == 0，所需的路径和当然就是 matrix[0][j] 呗。
        if (i == 0) {
            return matrix[0][j];
        }

        // 3.查找备忘录，防止重复计算
        if (memo[i][j] != 66666) {
            return memo[i][j];
        }

        // 状态转移
        memo[i][j] =  matrix[i][j] + min({
            dp(matrix, i-1, j),
            dp(matrix, i-1, j-1),
            dp(matrix, i-1, j+1) // i - 1, j - 1, j + 1 这几个运算可能会造成索引越界
        });

        return memo[i][j];
    }
};



