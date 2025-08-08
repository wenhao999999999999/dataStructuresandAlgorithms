#include <bits/stdc++.h>
using namespace std;

// 二分查找框架
// int binarysearch(vector<int>& nums, int target) {

//     int left = 0;
//     int right = nums.size() - 1;

//     while(...) {
        // int mid = left + (right - left) / 2; // 防止 mid 溢出

//         if (nums[mid] == target) {

//         }else if (nums[mid] < target) {
//             left = ...
//         }else if (nums[mid] > target) {
//             right = ...
//         }
//     }
// }

// 搜索目标元素的索引，若不存在则返回 -1
int search (vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else if (nums[mid] < target) {
            left = mid + 1;
        }
    }
    return -1;
}

// 寻找左侧边界
// 如果 target 不存在，搜索左侧边界的二分搜索返回的索引是大于 target 的最小索引。
int left_bound(vector<int>& nums, int target) {
    int left = 0;
    // int right = nums.size();
    int right = nums.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            right = mid - 1;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else if (nums[mid] < target) {
            left = mid + 1;
        }
    }

    // 判断左侧边界索引是否越界
    if (left < 0 || left >= nums.size()) return -1;

    // 判断nums[left] 是否等于 target
    return nums[left] == target ? left : -1;
}

// 寻找右侧边界
int right_bound(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else if (nums[mid] < target) {
            left = mid + 1;
        }
    }

    if (right < 0 || right > nums.size()) {
        return -1;
    }

    return nums[target] == target ? right : -1;
}

// 二分查找
// 给定字符串 s 和字符串数组 words, 返回  words[i] 中是s的子序列的单词个数 。字符串的 子序列 是从原始字符串中生成的新字符串，可以从中删去一些字符(可以是none)，而不改变其余字符的相对顺序。
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        
    }
};