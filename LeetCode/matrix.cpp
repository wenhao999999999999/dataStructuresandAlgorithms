# include <bits/stdc++.h>
using namespace std;
// 面试经典题：矩阵

// 1.矩阵置零
// 给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。

// 注意：这里时将 0 元素所在的所有元素都置为0，不只是相邻元素

// 解题思路：先用两个集合（或布尔数组）记录「需要置零的行」和「需要置零的列」；遍历矩阵，当遇到元素为 0 时，将其所在行和列加入集合；再次遍历矩阵，若元素所在行或列在集合中，则将该元素设为 0。

class Solution {
private:
    unordered_set<int> zero_rows, zero_cols;
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        // 第一步：记录需要置零的行和列
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    zero_rows.insert(i);
                    zero_cols.insert(j);
                }
            }
        }

        // 第二步：根据记录置零
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (zero_rows.count(i) || zero_cols.count(j)) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};