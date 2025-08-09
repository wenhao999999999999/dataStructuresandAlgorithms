#include <bits/stdc++.h>
using namespace std;
// 滑动窗口练习

// 滑动窗口可以归为快慢双指针，一快一慢两个指针前后相随，中间的部分就是窗口。滑动窗口算法技巧主要用来解决子数组问题，比如让你寻找符合某个条件的最长/最短子数组。


// 滑动窗口解题框架
// int slidwindow (vector<int>& nums){
//     int left = 0;
//     int right = 0;

//     while (right < nums.size()) {
//         // 增大窗口
//         window.addLast(nums[right]);
//         right++;

//         while (window need to shrink) {
//             // 缩小窗口
//             window.removeFirst(nums[left]);
//             left++:
//         }
//     }
// }
// 基于滑动窗口算法框架写出的代码，时间复杂度是 O(N)


// 滑动窗口伪代码框架

// int slidingWindow(string s) {
//     // 用合适的数据结构记录窗口中的数据，根据具体场景变通
//     // 比如说，我想记录窗口中元素出现的次数，就用 map
//     // 如果我想记录窗口中的元素和，就可以只用一个 int
//     // auto window = ...;

//     int left = 0, right = 0;
//     while (right < s.size()) {
//         // c 是将移入窗口的字符
//         char c = s[right];
//         window.add(c);
//         right++;

//         // 进行窗口内数据的一系列更新
//         // ...

//         // *** debug 输出的位置 ***
//         // printf("window: [%d, %d)\n", left, right);

//         while(window needs shrink) {
//             // // d 是将移出窗口的字符
//             char d = s[left];
//             window.remove(d);
//             left++;

//             // 进行窗口内数据的一系列更新
//             // ...
//         }

//     }
// }

// 基于这个框架，遇到子串/子数组相关的题目，你只需要回答以下三个问题：
// 1、什么时候应该移动 right 扩大窗口？窗口加入字符时，应该更新哪些数据？
// 2、什么时候窗口应该暂停扩大，开始移动 left 缩小窗口？从窗口移出字符时，应该更新哪些数据？
// 3、什么时候应该更新结果？

// 练习题
// 1.长度最小的子数组
// 给定一个含有 n 个正整数的数组和一个正整数 target 。找出该数组中满足其总和大于等于 target 的长度最小的 子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

class Solution {
public:
    // 算法流程：定义两个指针，维护一个窗口；定义 sum 变量，记录窗口 [left, right) 内元素的和；扩大窗口条件： right < nums.size()，更新 sum；缩小窗口条件：sum >= target;定义一个 res ,维护结果；如果 sum >= target , 更新res;
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0, right = 0;
        int sum = 0;
        int res = INT_MAX;

        // 扩大窗口条件
        while (right < nums.size()) {
            // 更新窗口和数据
            sum += nums[right];
            // 更新右指针
            right++;

            // 缩小窗口条件
            while (sum >= target) {
                // 更新结果
                res = min(res, right - left);

                // 更新和
                sum -= nums[left];
                left++;
            }
        }

        // 注意：当所有元素和都小于 target时，要返回 0；

        return res == INT_MAX ? 0 : res;
    }
};