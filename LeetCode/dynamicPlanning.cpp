// 动态规划解题套路框架
# include <bits/stdc++.h>
using namespace std;

// 首先，虽然动态规划的核心思想就是穷举求最值，但是问题可以千变万化，穷举所有可行解其实并不是一件容易的事，需要你熟练掌握递归思维，只有列出正确的「状态转移方程」，才能正确地穷举。
// 而且，你需要判断算法问题是否具备「最优子结构」，是否能够通过子问题的最值得到原问题的最值。
// 另外，动态规划问题存在「重叠子问题」，如果暴力穷举的话效率会很低，所以需要你使用「备忘录」或者「DP table」来优化穷举过程，避免不必要的计算。

// 动态规划的三要素：1.状态转移方程；2.最优子结构；3.重叠子问题
// 写状态转移方程思路：明确状态，也就是原问题和子问题中会变化的变量（一般是函数入参）-> 明确选择，也就是导致「状态」产生变化的行为 -> 明确dp函数的定义，返回值一般是题目要求我们计算的量。


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

        // 注意：res 要定义在 dp 函数体内部
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

// 4.单词拆分
// 给你一个字符串 s 和一个字符串数组 wordDict 作为字典，
// 请你判断是否可以利用字典中的单词拼接出 s 。
class Solution {
private:
    vector<string> wordDict;
    // 记录是否找到一个合法的答案
    bool found = false;

    // 记录回溯算法的路径
    vector<string> path;

    // 备忘录,存储不能切分的子串（子树），从而避免重复计算
    // 注意：这里使用 unordered_set 而不是 vector，因为我们只需要判断是否存在某个子串，而不需要知道它的具体位置
    // 这里的子串是 s 的一部分，所以我们使用 string 类型
    unordered_set<string> memo;
public:
    // 回溯算法
    bool wordBreak(string s, vector<string>& wordDict) {
        this->wordDict = wordDict;

        // 执行回溯算法，穷举所有可能的组合
        backtrack(s, 0);
        return found;
    }

    // 回溯算法框架
    void backtrack(string& s, int i) {
        // base case
        if (found) return; // 如果已经找到一个合法的答案，就不需要继续回溯了

        if (i == s.size()) {
            found = true; // 找到一个合法的答案
            return;
        }

        // 查询子串是否已经计算过
        string sub = s.substr(i);
        if (memo.count(sub)) {
            return; // 如果子串已经计算过，说明它不能切分，直接返回
        }

        // 回溯算法框架
        for (string& word : wordDict) {
            // 看看哪个单词能够匹配 s[i..i+len]
            int len = word.size();

            // 注意：这里的 i + len 不能超过 s.size()
            if (i+len <= s.size() && s.substr(i, len) == word) {
                // 找到一个单词匹配 s[i..i+len]
                // 做选择
                path.push_back(word);

                // 继续回溯,进入回溯树的下一层
                backtrack(s, i + len);

                // 撤销选择
                path.pop_back();
            }
        }

        // 后序位置，将不能切分的子串加入备忘录
        if (!found) {
            memo.insert(sub);
        }
    }
};

// 动态规划解法
class Solution {
private:
    unordered_set<string> wordDict;
    // 备忘录，-1 代表未计算，0 代表无法凑出，1 代表可以凑出
    vector<int> memo;
public:
    // 主函数
    bool wordBreak(string s, vector<string>& wordDict) {
        // 转化为哈希集合，快速判断元素是否存在
        for (auto &word : wordDict) {
            this->wordDict.insert(word);
        }

        // 初始化备忘录，-1 表示未计算
        memo.resize(s.length(), -1);

        return dp(s, 0);

    }

    // dp函数定义：返回 s[i..]是否能够被拼出
    int dp(string s, int i) {
        // base case
        if (i == s.size()) {
            return true; // 如果 i 到达字符串末尾，说明已经成功拼出
        }

        // 检查备忘录,防止冗余计算
        if (memo[i] != -1) {
            return memo[i] == 0 ? false : true; // 如果备忘录中已经计算过，直接返回结果
        }

        // 遍历字典中的单词
        for (auto &word : wordDict) {
            // 判断 s[i..i+len] 是否等于 word
            int len = word.size();
            if (s.substr(i, len) == word) {
                // 如果匹配成功，继续递归检查剩余部分
                if (dp(s, i + len)) {
                    memo[i] = 1; // 标记为可以拼出
                    return true; // 找到一个可以拼出的方案，直接返回
                }
            }
        }

        memo[i] = 0; // 标记为无法拼出
        return false; // 如果没有找到任何可以拼出的方案，标记为无法拼出
    }
};

// 4.2 单词拆分Ⅱ
// 给你一个字符串 s 和一个字符串数组 wordDict 作为字典，
// 请你将 s 中所有可以由字典中的单词组成的部分进行拆分，并返回所有可能的结果。
class Solution {
public:

};

// 5. 子序列类型问题
// 5.1 最大子数组和
// 给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

// 滑动窗口解法：大于等于0时，扩大窗口；小于0时，缩小窗口
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        int right =0;
        int max_sum = INT_MIN;
        int cur_sum = 0;

        while (right < n) {
            // 扩大窗口
            cur_sum += nums[right];
            right++;

            // 更新答案
            max_sum = max(max_sum, cur_sum);

            // 缩小窗口
            while (cur_sum < 0) {
                cur_sum -= nums[left];
                left++;
            }
        }

        return max_sum;
    }
};

// 动态规划解法：以 nums[i] 为结尾的「最大子数组和」为 dp[i]，状态转移方程为：
// dp[i] = max(dp[i-1] + nums[i], nums[i])
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        // dp 数组定义：dp[i] 表示以 nums[i] 这个数结尾的最大子数组和
        vector<int> dp(n, 0);

        // base case
        dp[0] = nums[0];

        // 状态转移
        for (int i = 1; i < n; i++) {
            dp[i] = max(dp[i-1]+nums[i], nums[i]);
        }

        // 找到最大值
        int max_sum =  INT_MIN;
        for (int i = 0; i < n; i++) {
            max_sum = max(max_sum, dp[i]);
        }

        return max_sum;
    }
};

// 前缀和解法：
// 前缀和数组 pre_sum[i] 表示 nums[0..i-1] 的前缀和，即 pre_sum[i] = nums[0] + nums[1] + ... + nums[i-1]
// 则preSum[i+1] - preSum[j] 其实就是子数组 nums[j..i] 之和。那么反过来想，以 nums[i] 为结尾的最大子数组之和是多少？其实就是 preSum[i+1] - min(preSum[0..i])。
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        // 前缀和数组
        vector<int> pre_sum(n+1, 0);
        for (int i = 1; i <= n; i++) {
            pre_sum[i] = pre_sum[i-1] + nums[i-1];
        }

        // 最大子数组和
        int max_sum = INT_MIN;
        int min_pre_sum = INT_MAX;
        for (int i = 0; i < n; i++) {
            min_pre_sum = min(min_pre_sum, pre_sum[i]);
            max_sum = max(max_sum, pre_sum[i+1] - min_pre_sum);
        }

        return max_sum;
    }
};

// 5.2 最长公共子序列
// 给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

// 动态规划解法：自顶向下
class Solution {
private:
    // 备忘录，消除重叠子问题
    vector<vector<int>> memo;

public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();

        // 备忘录初始化值为-1，表示未计算
        memo = vector<vector<int>> (m, vector<int>(n, -1));
        return dp(text1, text2, 0, 0);
    }

    // 状态转移方程定义：计算 s1[i..] 和 s2[j..] 的最长公共子序列的长度
    int dp(string s1, string s2, int i, int j) {
        // base case
        if (i == s1.size() || j == s2.size()) {
            return 0;
        }

        // 避免重复计算
        if (memo[i][j] != -1) return memo[i][j];

        // 状态转移
        if (s1[i] == s2[j]) {
            // s1[i] 和 s2[j] 必然在公共子序列中，加s1[i+1..] 和 s2[j+1..]的最长公共子序列长度， 就是答案
            memo[i][j] = 1+dp(s1, s2, i+1, j+1);
        }else {
            // s1[i] 和 s2[j] 中至少有一个字符不在公共子序列中，穷举三种情况的结果，取其中对大的结果
            memo[i][j] = max (
                // 情况一：s1[i] 不在公共子序列中
                dp (s1, s2, i+1, j),
                // 情况二： s2[j] 不在公共子序列中
                dp (s1, s2, i, j+1)
            );
        }

        return memo[i][j];
    }
};

// 动态规划解法：自底向上
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();

        // 定义二维数组 dp，dp[i][j] 表示 text1[0..i-1] 和 text2[0..j-1] 的最长公共子序列的长度
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        // 目标：text1[0..m-1] 和 text2[0..n-1] 的最长公共子序列的长度，即 dp[m][n]
        // base case: dp[0][..] = dp[..][0] = 0

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i-1] == text2[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[m][n];
    }
};


