#include <bits/stdc++.h>
using namespace std;
// 区间问题练习

// 1.插入区间
// 给你一个 无重叠的 ，按照区间起始端点排序的区间列表 intervals，其中 intervals[i] = [starti, endi] 表示第 i 个区间的开始和结束，并且 intervals 按照 starti 升序排列。同样给定一个区间 newInterval = [start, end] 表示另一个区间的开始和结束。
class Solution {
public:
    // 解题思路：步骤 1：处理不重叠的前置区间：遍历 intervals，将所有结束位置小于 newInterval 起始位置的区间直接加入结果；步骤 2：合并重叠区间：当遇到与 newInterval 重叠的区间，不断更新 newInterval 的左右边界：左边界取两者较小值；右边界取两者较大值；直到遍历完所有重叠区间，将最终合并后的 newInterval 加入结果。步骤 3：处理不重叠的后置区间：将剩余不重叠且在 newInterval 之后的区间，直接加入结果。
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res; // 存储最终结果
        int i = 0;                  // 遍历原区间的指针
        int n = intervals.size();    // 原区间数量

        // 步骤 1：添加新区间前的不重叠区间
        while (i < n && intervals[i][1] < newInterval[0]) {
            res.push_back(intervals[i]);
            i++;
        }

        // 步骤 2：合并所有重叠区间
        // 如果原区间的起始位置 <= 新区间的结束位置，说明两个区间有重叠
        while (i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]); // 更新合并后的左边界
            newInterval[1] = max(newInterval[1], intervals[i][1]); // 更新合并后的右边界 
            i++;
        }

        res.push_back(newInterval);

        // 步骤 3：添加新区间后的不重叠区间
        while (i < n) {
            res.push_back(intervals[i]);
            i++;
        }

        return res;
    }
};