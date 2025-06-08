#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used;

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
};

int main() {
    vector<int> nums = {1, 2, 3};
    Solution sol;
    vector<vector<int>> res = sol.allPermute(nums);
    for (auto& vec : res) {
        for (auto& num : vec) {
            cout << num << " ";
        }
        cout << endl;
    }   
    return 0;
}