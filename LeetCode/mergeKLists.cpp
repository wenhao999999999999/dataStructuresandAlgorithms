#include <bits/stdc++.h>
#include <../include/linkedList.h>
using namespace std;

//1. 合并两个有序链表
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


int main() {

    //实例化3个链表对象
    LinkedList list1;
    LinkedList list2;

    list1.addLast(1);
    list1.addLast(4);
    list1.addLast(5);

    list2.addLast(1);
    list2.addLast(3);
    list2.addLast(4);
    
}