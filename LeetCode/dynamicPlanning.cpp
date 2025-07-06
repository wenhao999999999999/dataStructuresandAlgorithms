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



