#include <bits/stdc++.h>
using namespace std;
// 数组快慢指针问题

// 1.删除有序数组中的重复项
// 给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使得出现次数超过两次的元素只出现两次 ，返回删除后数组的新长度。不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

class Solution {
public:
    // 解题思路：定义两个指针和一个计数变量，维护nums[0..i]元素出现次数不超过 2 次
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) return nums.size();

        int slow = 0;
        int fast = 0;
        int count = 0;

        while (fast < nums.size()) {
            // 如果新元素与当前元素不相等可以直接赋值
            if (nums[fast] != nums[slow]) {
                // 注意：先+1，再赋值
                slow++;
                nums[slow] = nums[fast];
            // 注意：这里的判断条件是slow < fast 
            } else if (slow < fast && count < 2) {
                // 注意：先+1，再赋值
                slow++;
                nums[slow] = nums[fast];
            }

            // 快指针向前移动
            fast++;
            count++;
            // 注意：这里的
            if (fast < nums.size() && nums[fast] != nums[fast - 1]) {
                // fast 遇到新的不同元素，重置 count
                count = 0;
            }
        }
        return slow + 1;
    }
};

// 2.轮转数字
// 给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
// 原地修改：第一次反转全部元素；第二次反转前 k 个元素；第三次反转其余元素
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n; // 处理 k 大于数组长度的情况，取余后得到实际需要轮转的步数
        // 第一次反转整个数组
        reverse(nums.begin(), nums.end());
        // 第二次反转前 k 个元素
        reverse(nums.begin(), nums.begin() + k);
        // 第三次反转剩下的元素
        reverse(nums.begin() + k, nums.end());
    }
};


// 3.多数元素
// 给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。你可以假设数组是非空的，并且给定的数组总是存在多数元素。

// 哈希表解法：用一个哈希表记录数组中每个元素出现的次数
class Solution {
private:
    // 初始化一个哈希表，统计数组中每个元素出现的次数
    unordered_map<int,int> mp;
public:
    int majorityElement(vector<int>& nums) {
        int res = 0;
        int count = 0;
        for (auto num : nums) {
            mp[num]++;
        }

        for(auto num : nums) {
            if (count < mp[num]){
                res = num;
                count = mp[num];
            }
                
        }

        return res;
    }
};

// 摩尔投票解法：
// 维护一个候选多数元素和一个计数器。遍历数组时，遇到相同的元素则计数器加 1，遇到不同的元素则计数器减 1。当计数器为 0 时，更换候选元素为当前元素，并将计数器重置为 1。最终，候选元素即为多数元素（因为题目保证数组中一定存在多数元素）。

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // 计数器
        int count = 0;

        // 候选元素
        int target = 0;

        for (int i  = 0; i < nums.size(); i++) {
            if (count == 0) {
                target = nums[i];
                count = 1;
            }else if (target == nums[i]) {
                count++;
            } else {
                count--;
            }
        }

        return target;
    }
};

// 最大子数组和问题/Kadane 算法

