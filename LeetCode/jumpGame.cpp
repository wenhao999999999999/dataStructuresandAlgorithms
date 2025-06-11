#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    vector<int> memo;
public:
    bool canJump(vector<int> &nums) {
        int n = nums.size();
        int farthest = 0;
        for (int i = 0; i < n - 1; i++) {
            //贪心算法：谁能走得最远，你就选谁，准没错
            farthest = max(farthest, i + nums[i]);
            //可能碰到了 0，卡住跳不动了
            if (farthest <= i) {
                return false;
            }
        }
        return farthest >= n - 1;
    }

    //最小跳跃次数，动态规划解法
    //定义dp函数：从当前位置到终点得最小步数；状态：当前的位置p;选择：跳跃多少步；
    int dp (vector<int>& nums, int p) {
        int n = nums.size();
        //base case
        if (p >= n - 1) {
            return 0;
        }

        //剪枝
        if (memo[p] != n) {
            return memo[p];
        }

        int steps = nums[p];
        for (int i = 1; i <= steps; i++) {
            int subProblem = dp(nums, p + i);
            memo[p] = min(memo[p], subProblem + 1);
        }
        return memo[p];
    }

    int jumpMin(vector<int>& nums) {
        int n = nums.size();
        memo = vector<int>(n,n);
        return dp(nums, 0);
    }

};

int main() {
    Solution sol;
    vector<int> nums;
    int n;
    cin >> n;
    nums.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    // cout << sol.canJump(nums);
    cout << sol.jumpMin(nums);
}