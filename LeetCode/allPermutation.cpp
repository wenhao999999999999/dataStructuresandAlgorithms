#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used;
public:
    void backtracking(vector<int>& nums) {

        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        int sz = nums.size();
        for (int i = 0; i < sz; i++) {
            if(used[i]) continue;
            used[i] = true;
            path.push_back(nums[i]);
            backtracking(nums);
            path.pop_back();
            used[i] = false;
        }
    }

    vector<vector<int>> allPermute(vector<int>& nums) {
        used.resize(nums.size(), false);
        backtracking(nums);
        return result;
    }

    void backtrackingUnique(vector<int>& nums) {

        //base case
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }

        int sz = nums.size();
        for (int i = 0; i < sz; i++) {
            if (used[i]) continue;
            //剪枝，保证相邻相等元素的相对顺序
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) {
                continue;
            }

            //choose
            path.push_back(nums[i]);
            used[i] = true;

            //recursion
            backtrackingUnique(nums);

            //撤销选择
            path.pop_back();
            used[i] = false;
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        used.resize(nums.size(), false);
        backtrackingUnique(nums);
        return result;
    }
};



int main() {
    vector<int> nums = {1, 2, 3};
    vector<int> nums2 = {1, 2, 2};
    Solution sol;
    // vector<vector<int>> res = sol.allPermute(nums);
    vector<vector<int>> res2 = sol.permuteUnique(nums2);
    for (auto& vec : res2) {
        for (auto& num : vec) {
            cout << num << " ";
        }
        cout << endl;
    }   
    return 0;
}