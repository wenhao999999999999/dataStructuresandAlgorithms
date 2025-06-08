#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> result;
    vector<int> track;

    void backtracking(int n, int k, int start) {
        int sz = track.size();
        if (sz == k) {
            result.push_back(track);
            //提前终止，避免冗余计算
            return;
        }

        for(int i = start; i <= n; i++){
            track.push_back(i);
            backtracking(n, k, i+1);
            track.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        backtracking(n, k, 1);
        return result;
    }
};

int main() {
    Solution s;
    vector<vector<int>> result = s.combine(4, 2);
    for (auto vec : result) {
        for (int num : vec) {            
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}   