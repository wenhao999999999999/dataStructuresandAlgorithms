// 括号类问题汇总
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:

    // 1.有效的括号
        // 输入：一个字符串
        // 返回：字符串是否有效
    bool isValid(string s) {
        // 初始化一个栈，用于存储左括号
        stack<char> stk;

        for (auto c : s) {
            if (c == '('|| c == '[' || c == '{') {
                stk.push(c);
            // 注意：要先判断栈是否为空，否则会报错
            } else if (!stk.empty() && leftOf(c) == stk.top()) {
                stk.pop();
            } else {
                return false;
            }
        }
        return stk.empty();
    }

    // 辅助函数：根据右括号类型并返回适配的的左括号
    char leftOf(char c) {
        if (c == ')') return '(';
        if (c == ']') return '[';
        return '{';
    }

    // 2.使括号有效的最少添加
        // 输入：字符串 s
        // 返回：为使结果字符串 s 有效而必须添加的最少括号数
    int minAddToMakeValid(string s) {
        // 右括号的需求数量
        int need = 0;

        // 左括号的需求数量
        int res = 0;

        int sz = s.size();
        for (int i = 0; i < sz; i++) {

            // 如果当前字符时左括号，就需要一个右括号
            if (s[i] == '(') {
                need++;
            } else {
                // 如果当前字符是右括号，右括号的需求就可以满足1个
                need--;
                // 如果目前的右括号多出来了，没有与他匹配的左括号
                if (need == -1) {
                    // 需要插入一个左括号；
                    res++;
                    // 正好匹配，不需要插入右括号了
                    need = 0;
                }
            }
        }
        // 返回需要插入的左右括号总数
        return res + need;
    } 
    
    // 3.平衡括号字符串的最少插入次数
        // 输入：字符串 s
        // 返回：让 s 平衡的最少插入次数
        // 一个括号字符串被称为平衡的当它满足：
            // 任何左括号 '(' 必须对应两个连续的右括号 '))' 。
            // 左括号 '(' 必须在对应的连续两个右括号 '))' 之前。
            // 比方说 "())"， "())(())))" 和 "(())())))" 都是平衡的， ")()"， "()))" 和 "(()))" 都是不平衡的。
        // 你可以在任意位置插入字符 '(' 和 ')' 使字符串平衡。
    int minInsertions(string s) {
        // need 记录右括号的需求量
        int need = 0;

        // 记录需要插入的括号总数
        int res = 0;

        for (int i = 0; i < s.length(); i++) {
            // 一个左括号对应两个右括号
            if (s[i] == '(') {
                need += 2;

                // 如果当前需要的右括号数是奇数，说明前面出问题了
                if (need % 2 == 1) {
                    // 插入一个右括号来补全之前的需求
                    res++;

                    //减少一个需求（让 need 从奇数变成偶数）
                    need--; 
                }
            }

            if (s[i] == ')') {
                need--;
                if (need == -1) {
                    // 需要插入一个左括号
                    res++;
                    // 一个左括号对应2个右括号，但现在多出来1个，还需要1个
                    need = 1;
                }
            }
        }

        // res 是过程中需要插入的括号数（包括多插的 ')' 或 '('）
        // need 是最后还差的 ')' 数量（即闭合用的右括号）
        return res + need;
    }
};