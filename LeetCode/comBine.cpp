#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> result;
    vector<int> track;

    //用于记录当前路径的元素和
    int tracksum = 0;


    //目标个数的组合
    void backtracking(int n, int k, int start) {
        int sz = track.size();
        //base case 
        if (sz == k) {
            result.push_back(track);
            //提前终止，避免冗余计算
            return;
        }

        for(int i = start; i <= n; i++){
            //选择
            track.push_back(i);
            //递归
            backtracking(n, k, i+1);
            //撤销选择
            track.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        backtracking(n, k, 1);
        return result;
    }

    //目标和的组合,不可重复
    void backtracking2(int target, int start, vector<int>& candidates) {
        //base case
        if (tracksum == target) {
            result.push_back(track);
            return; 
        }

        if (tracksum > target) {
            return;
        }

        int sz = candidates.size();
        for(int i = start; i < sz; i++) {
            //跳过相同项
            if (i > start && candidates[i] == candidates[i-1]) {
                continue;
            }
            //选择
            track.push_back(candidates[i]);
            tracksum += candidates[i];
            //递归
            backtracking2(target, i+1, candidates);

            //撤销选择
            track.pop_back();
            tracksum -= candidates[i];
        }
    }

    vector<vector<int>> combineSum(int target, vector<int>& candidates) {
        //排序，使得相同元素相邻,用于处理输入数组中含相同元素的情况
        sort(candidates.begin(), candidates.end());
        backtracking2(target, 0, candidates);
        return result;

    }

    //输入数组无重复，元素可重复使用
    void backtrackint3(int start, int target, vector<int> nums) {
        //base case
        if (tracksum == target) {
            result.push_back(track);
            return;
        }

        if (tracksum > target) {
            return;
        }
        int sz = nums.size();
        for (int i = start; i < sz; i++){
            //做选择
            track.push_back(nums[i]);
            tracksum += nums[i];

            //递归
            backtrackint3(i, target, nums);

            //撤销选择
            track.pop_back();
            tracksum -= nums[i];
        }
        
        
        
    }

    vector<vector<int>> combineSum2(vector<int>& candidates, int target) {
        backtrackint3(0, target, candidates);
        return result;
    }

};

int main() {
    Solution s;
    // vector<vector<int>> result = s.combine(4, 2);
    // vector<int> candidates = {10,1,2,7,6,1,5};
    vector<int> candidates = {2,3,6,7};
    vector<vector<int>> result2 = s.combineSum2(candidates, 7);
    for (auto vec : result2) {
        for (int num : vec) {            
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}   