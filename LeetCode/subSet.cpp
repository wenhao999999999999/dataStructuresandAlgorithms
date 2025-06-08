#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> result;
    vector<int> track;

    void backtracking(vector<int>& nums, int start) {
        result.push_back(track);
        int sz = nums.size();
        for (int i = start; i < sz; i++){
            track.push_back(nums[i]);
            backtracking(nums, i+1);
            track.pop_back();
        }
    }

    vector<vector<int>> subSets(vector<int>& nums) {
        backtracking(nums, 0);
        return result;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1, 2, 3};
    auto result = s.subSets(nums);
    for (auto vec : result) {
        for (auto num : vec) {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}