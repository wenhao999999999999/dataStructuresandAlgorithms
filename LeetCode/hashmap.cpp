#include <bits/stdc++.h>
using namespace std;
// 哈希表练习题目

// 1.最长连续序列
// 给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。请你设计并实现时间复杂度为 O(n) 的算法解决此问题。
class Solution {
public:
    // 解题思路：将数组转换为哈希集合，快速判断某个元素是否存在并自动去重；遍历集合，找到连续序列的起点；计算以起点开始的连续序列的长度；返回结果 
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> set(nums.begin(), nums.end());
        // 存储结果
        // 注意：结果应该初始化为0，而不是INT_MIN，对应空数组的情况
        int res = 0;

        // 判断某个元素是否为序列起点
        // 注意：这里要遍历集合而不是遍历数组
        for (auto num : set) {
            if (set.find(num - 1) != set.end()) {
                continue;
            }

            // 当前起点
            int curnum = num;
            // 初始长度
            int curlen = 1;

            while (set.find(curnum+1) != set.end()) {
                curnum++;
                curlen++;
            }

            res = max(res, curlen);
        }

        return res;
    }
};

// 2.赎金信
// 给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine 里面的字符构成。如果可以，返回 true ；否则返回 false 。magazine 中的每个字符只能在 ransomNote 中使用一次。
// 解题思路：用哈希表存储 magazine 中的字符出现的次数；遍历字符串 ransomNote ，判断哈希表中是否包含所有字符；
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> map;

        for (auto c : magazine) {
            map[c]++;
        }

        for (auto c : ransomNote) {
            if (!map.count(c)) return false;
            map[c]--;
            if (map[c] == 0) map.erase(c);
        }

        return true;
    }
};
