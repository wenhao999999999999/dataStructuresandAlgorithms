#include <bits/stdc++.h>
using namespace std;
// 双指针问题

// 1.判断子序列
// 给定字符串 s 和 t ，判断 s 是否为 t 的子序列。字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。
// 进阶：如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？

// 解题思路：定义两个指针i,j，分别指向两个字符串s, t，遍历字符串 t ,指针 j 不断右移，判断两指针所指字符是否相等。
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0;
        int j = 0;

        while (j < t.size()) {
            if (s[i] == t[j]) {
                i++;
            }
            j++;
        }

        return i == s.size();
    }
};

