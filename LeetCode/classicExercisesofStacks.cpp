// 力扣中栈的经典习题
#include <bits/stdc++.h>
#include "../include/linkedList.h"
using namespace std;

class Solution {
public:
    // 1.简化路径，给你一个字符串 path ，表示指向某一文件或目录的 Unix 风格 绝对路径 （以 '/' 开头），请你将其转化为 更加简洁的规范路径。
    // 在 Unix 风格的文件系统中规则如下：
        // 一个点 '.' 表示当前目录本身。
        // 此外，两个点 '..' 表示将目录切换到上一级（指向父目录）。
        // 任意多个连续的斜杠（即，'//' 或 '///'）都被视为单个斜杠 '/'。
        // 任何其他格式的点（例如，'...' 或 '....'）均被视为有效的文件/目录名称。
    // 返回的 简化路径 必须遵循下述格式：
        // 始终以斜杠 '/' 开头。
        // 两个目录名之间必须只有一个斜杠 '/' 。
        // 最后一个目录名（如果存在）不能 以 '/' 结尾。
        // 此外，路径仅包含从根目录到目标文件或目录的路径上的目录（即，不含 '.' 或 '..'）。
        // 返回简化后得到的 规范路径 。

    string simplifyPath(string path) {
        vector<string> parts;
 
        // 实例化一个输入字符串流，用于解析有效路径
        istringstream ss(path);

        // 临时存储当前目录
        string part;

        // 借助栈解析最终的文件夹路径
        while (getline(ss, part, '/')) {
            // 当前目录本身或者为空，跳过
            if (part.empty() || part == ".") {
                continue;
            }
            // 目录切换到上一级
            if (part == "..") {
                // 目前已经解析的路径非空
                if (!parts.empty()) {
                    // 移除已经解析的最后一个目录
                    parts.pop_back();
                }
            }else {
                // 保存当前目录到结果路径中
                parts.push_back(part);
            }
        }

        // 栈中存储的文件夹组成路径
        string res;

        // 注意不可以改变原始路径
        for (const auto& p : parts) {
            res += "/" + p;
        }
        
        return res.empty() ? "/" : res;
    }

    // 2.重排链表
    // 给定一个单链表 L 的头节点 head ，单链表 L 表示为：
        // L0 → L1 → … → Ln - 1 → Ln
    // 请将其重新排列后变为：
        // L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
    // 不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
    void reorderList(ListNode* head) {
        // 初始化一个栈，用于存放链表的结点
        stack<ListNode*> stk;

        // 先把所有节点装进栈里，得到倒序结果
        ListNode* p = head;
        while (p != nullptr) {
            stk.push(p);
            p = p->next;
        }

        p = head;

         while (!stk.empty()) {
            // 链表尾部的节点
            ListNode* lastNode = stk.top();
            stk.pop();

            // 存储当前节点的下一个结点
            ListNode* next = p->next;

            if (lastNode == next || lastNode->next == next) {
                //偶数 || 奇数长度链表结束条件
                //注意：指针指向空
                lastNode->next = nullptr;
                break;
            }

            p->next = lastNode;
            lastNode->next = next;
            p = next;
         }    
    }

    // 3.有效的括号
    // 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
    // 有效字符串需满足：
        // 左括号必须用相同类型的右括号闭合。
        // 左括号必须以正确的顺序闭合。
        // 每个右括号都有一个对应的相同类型的左括号。
    bool isValid(string s) {
        // 存储左括号的栈
        stack<char> left;

        // 遍历字符串中的括号
        for (char c : s) {

            // 如果是左括号就入栈
             if (c == '(' || c == '{' || c == '[') {
                left.push(c);

            // 字符 c 是右括号
             } else {
                if (!left.empty() && leftOf(c) == left.top()) {
                    left.pop();
                } else {

                    // 和最近的左括号不匹配
                    return false;
                }
             }
        }
        // 是否所有的左括号都被匹配了
        // 注意：这里不是直接返回true
        return left.empty();
    } 
    
    char leftOf(char c) {
        if (c == '}') return '{';
        if (c == ')') return '(';
        return '[';
    }

    // 4.逆波兰表达式求值
        // 给你一个字符串数组 tokens ，表示一个根据逆波兰表示法表示的算术表达式。
        // 请你计算该表达式。返回一个表示表达式值的整数。
        // 解题思路：按顺序遍历逆波兰表达式中的字符，如果是数字，则放入栈；如果是运算符，则将栈顶的两个元素拿出来进行运算，再将结果放入栈。对于减法和除法，运算顺序别搞反了，栈顶第二个数是被除（减）数。
    int evalRPN(vector<string>& tokens) {
        // 初始化一个栈，用于存放操作数
        stack<int> stk;

        // 遍历字符串
        for (const std::string& token : tokens) {

            //如果是运算符
            if (token == "+" || token == "-" || token == "*" || token == "/") {

                //从栈顶拿出两个数字进行运算，运算结果入栈
                int a = stk.top(); stk.pop();
                int b = stk.top(); stk.pop(); 
                
                if (token == "+") stk.push(b + a);
                else if (token == "*") stk.push(b * a);
                else if (token == "-") {
                    // 对于减法和除法，顺序别搞反了，第二个数是被除（减）数
                    stk.push(b - a);
                }
                else if (token == "/") stk.push(b / a);                
            } else {
                //如果是个数字，直接入栈即可
                stk.push(stoi(token));
            }
        }
        
        // 最后栈中剩下一个数字，即是计算结果
         return stk.top();
    }

    // 5.文件的最长绝对路径
    int lengthLongestPath(string input) {
        
        // 存储当前路径中每一层目录/文件名的长度（不含 /）。
        deque<int> stack;
        // 记录最长路径长度
        int maxLen = 0;

        // 把原始字符串按 '\n' 拆成多行，每一行一个目录或文件。
        vector<string> parts = split(input, '\n');
        
        for (const string& part : parts) {
            // level 是当前行的深度（\t 的数量），用 rfind("\t") + 1 得到
            int level = part.rfind("\t") + 1;

            // 如果当前目录层级比栈中的层级低，弹出多余层级，使栈保持正确的父路径结构。
            while (level < stack.size()) {
                stack.pop_back();
            }

            // 当前这层目录/文件的实际名字长度（去掉 \t）
            stack.push_back(part.size() - level);

            // 如果是文件，就计算路径长度
            if (part.find('.') != string::npos) {
                int sum = 0;
                for (int len : stack) {
                    sum += len;
                }
                sum += stack.size() - 1;  // 添加 `/` 分隔符数量
                maxLen = max(maxLen, sum);
            }
        }
        return maxLen;
    }

    // 工具函数：按分隔符切分字符串
    vector<string> split(const string& s, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
};


int main() {
    Solution sol;
    string path = "/home/";
    cout << sol.simplifyPath(path) << endl;
    return 0;

}