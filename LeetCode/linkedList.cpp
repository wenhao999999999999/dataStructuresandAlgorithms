// 链表经典题目

# include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* nxt) : val(x), next(nxt) {}
};

// 1. 环形链表
// 给你一个链表的头节点 head ，判断链表中是否有环。如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。

class Solution {
public:
    bool hasCycle(ListNode* head) {
        // 鲁棒性条件
        if (head == nullptr || head->next == nullptr) return false;

        // 定义快慢指针
        ListNode* p1 = head;
        ListNode* p2 = head;

        // 注意：循环条件为快指针不为空并且快指针的下一个节点也不为空
        while (p2 != nullptr && p2->next != nullptr) {
            p1 = p1->next;
            p2 = p2->next->next;

            // 注意：判断环是否存在的条件是快慢指针是否指向同一节点，而非判断节点的值是否相等
            if (p1 == p2) {
                return true;
            }
        }

        return false;
    }
};

// 2. 环形链表Ⅱ
// 给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        // 鲁棒性条件
        if (head == nullptr || head->next == nullptr) return nullptr;

        // 定义快慢指针
        ListNode* fast = head;
        ListNode* slow = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow) break;
        }

        if (fast != slow) return nullptr;

        slow = head;

        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};

// 3. 相交链表
// 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。

class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        //注意：鲁棒性条件
        if (headA == nullptr || headB == nullptr) return nullptr;

        // 定义两个指针分别指向两条链表
        ListNode* p1 = headA;
        ListNode* p2 = headB;

        // 注意：循环判定条件是量指针是否指向统一结点
        while (p1 !=  p2) {
            // 当指针在当前链表遍历到空指针时，从另一条链表开头开始遍历
            // 如果两链表没有交点，那么当指针下一次指向空时一定是同时指向空的，因此会跳出循环
            p1 = p1 == nullptr ? headB : p1->next;
            p2 = p2 == nullptr ? headA : p2->next;
        }

        return p1;
    }
};

// 4. 删除链表的倒数第N个结点
// 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
// 注意：要求只遍历一遍链表就得出答案
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 注意：为了让结果一般化，包含删除头结点的情况
        // 定义虚拟头节点
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;

        // 找到倒数第 n+1 个结点
        ListNode* node = findFromEnd(dummy, n+1);

        node->next = node->next->next;

        return dummy->next;
    }

    ListNode* findFromEnd(ListNode* head, int k) {
        // 定义两个指针
        ListNode* p1 = head;
        ListNode* p2 = head;

        // 先让 p1 走 n 步
        for (int i = 0; i < k; i++) {
            p1 = p1->next;
        }

        // 接着让 p1 和 p2 同步走，直到 p1 指向空结点
        while (p1 != nullptr) {
            p1 = p1->next;
            p2 = p2->next;
        }

        // 返回倒数第 k 个结点
        return p2;
    }

    
};

// 5. 合并链表
//5.1 合并两个有序链表
//输入：链表1，链表2
//返回：一个升序链表
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    //定义两个指针
    ListNode* p1 = list1;
    ListNode* p2 = list2;

    //定义一个虚拟头节点
    ListNode* dummy = new ListNode(-1);

    //创建的链表的尾结点
    ListNode* p = dummy;

    while(p1 != nullptr && p2 != nullptr) {
        if (p1->val < p2->val) {
            p->next = p1;
            p = p->next;
            p1 = p1->next;
        } else {
            p->next = p2;
            p = p->next;
            p2 = p2->next;
        }
    }
    if (p1 != nullptr) {
            p->next = p1;
    } else {
            p->next = p2;
    }
    return dummy->next;
}

// 2.1 合并K个升序链表,循环形式
//输入：K个链表
//返回:一个升序链表
ListNode* mergeKLists(vector<ListNode*> lists) {
    int sz = lists.size();
    //增强代码的鲁棒性
    if (sz == 0) return nullptr;

    //把k个有序链表都合并到lists[0]是上面
    ListNode* listNew = lists[0];
    for (int i = 1; i < sz; i++) {
        listNew = mergeTwoLists(listNew, lists[i]);
    }
    return listNew;
}

// 2.2 合并K个升序链表，递归形式
//输入：K个升序链表
//返回：1个升序链表
ListNode* mergeKLists2(vector<ListNode*> lists, int start) {
    //base case
    if (start == lists.size() - 1) {
        return lists[start];
    }

    //合并start+1...为一个链表
    ListNode* subLists = mergeKLists2(lists, start+1);

    //合并lists[start]和subLists，就得到完整的有序链表
    return mergeTwoLists(lists[start], subLists);
}

// 2.3 合并K个升序链表，递归形式,平衡递归树，减少链表的重复遍历次数，提高算法的效率
//输入：K个升序链表
//返回：1个升序链表
ListNode* mergeKLists3(vector<ListNode*> lists, int start, int end) {
    //base case
    if (start == end) {
        return lists[start];
    }
    
    //中间链表索引
    int mid = start + (end - start) / 2;

    //合并左半边
    ListNode* leftTree = mergeKLists3(lists, start, mid);

    //合并右半边
    ListNode* rightTree = mergeKLists3(lists, mid+1, end);

    //合并左右两个子链表
    return mergeTwoLists(leftTree, rightTree);
}

// 3.反转链表
// 函数定义：输入一个链表的头节点，返回反转之后的链表的头节点
ListNode* reverseList(ListNode* head) {

    // 注意：这里判断条件是或的关系
    if (head == nullptr || head->next == nullptr) return head;

    // 注意：这里返回的是头节点
    ListNode* last = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;

    return last;

}