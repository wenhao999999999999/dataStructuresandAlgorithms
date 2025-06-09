#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> result;
    vector<int> track;

    //元素不重复
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

    //元素可重复，子集不可重复
    void backtrackingUnique(vector<int>& nums, int start) {
        result.push_back(track);
        int sz = nums.size();
        for(int i = start; i < sz; i++) {
            if(i > start && nums[i] == nums[i-1]) {
                continue;
            }
            track.push_back(nums[i]);
            backtrackingUnique(nums, i+1);
            track.pop_back();
        }
    }

    vector<vector<int>> subSetUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        backtrackingUnique(nums, 0);
        return result;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1, 2, 3};
    vector<int> nums_2 = {1, 2, 2};
    auto result = s.subSetUnique(nums_2);
    for (auto vec : result) {
        for (auto num : vec) {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}