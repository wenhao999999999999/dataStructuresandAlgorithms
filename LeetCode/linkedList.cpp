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
// 题目描述：
    // 给你一个链表的头节点 head ，判断链表中是否有环。如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
// 解题思路：
    // 定义两个指针，其中一个快指针，一个慢指针，慢指针每走一步快指针走两步，判断快慢指针所指的结点是否为同一结点；
// 核心代码：
class Solution {
public:
    bool hasCycle(ListNode* head) {
        // 鲁棒性条件
        if (head == nullptr || head->next == nullptr) return false;

        // 定义快慢指针
        ListNode* p1 = head;
        ListNode* p2 = head;

        // 注意点1：循环条件为快指针不为空并且快指针的下一个节点也不为空
        while (p2 != nullptr && p2->next != nullptr) {
            p1 = p1->next;
            p2 = p2->next->next;

            // 注意点2：判断环是否存在的条件是快慢指针是否指向同一节点，而非判断节点的值是否相等
            if (p1 == p2) {
                return true;
            }
        }

        return false;
    }
};

// 2. 环形链表Ⅱ
// 题目描述：
    // 给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
// 解题思路：
    // 先用快慢指针的方法找到快慢指针相遇的结点的位置；其中一个指针从头节点开始遍历，另一个指针从相遇结点开始遍历，直到两个指针再次相遇，返回其中一个指针。
// 核心代码：
class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        // 鲁棒性条件
        if (head == nullptr || head->next == nullptr) return nullptr;

        // 定义快慢指针
        ListNode* fast = head;
        ListNode* slow = head;

        // 注意点1：循环条件为快指针不为空并且快指针的下一个节点也不为空
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow) break;
        }

        // 注意点2：要判断导致循环结束的条件是否为快慢指针相遇
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
// 题目描述：
    // 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。
// 解题思路：
    // 定义两个指针分别从两条链表的头节点开始遍历；当指针第一次到达空结点时，从另一条指针的头节点开始遍历；如果两条链表有交点，则退出循环并返回任一指针，如果两条链表没有交点，则一定同时指向空，逻辑相同，可以直接返回。
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        //注意：鲁棒性条件
        if (headA == nullptr || headB == nullptr) return nullptr;

        // 定义两个指针分别指向两条链表
        ListNode* p1 = headA;
        ListNode* p2 = headB;

        // 注意点1：循环判定条件是两指针是否指向同一结点
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
// 题目描述：
    // 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。注意：要求只遍历一遍链表就得出答案
// 解题思路：
    // 首先定义一个虚拟头节点，指向链表头节点，使得结果包含删除头节点的情况；然后找到链表的倒数第 n+1 个结点，删除链表的倒数第 n 个结点，返回链表的头节点；
// 核心代码：
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 注意点1：为了让结果一般化，包含删除头结点的情况，可以定义一个虚拟头节点
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;

        // 找到倒数第 n+1 个结点
        ListNode* node = findFromEnd(dummy, n+1);

        node->next = node->next->next;

        return dummy->next;
    }
    // 找到链表倒数第 n 个结点的算法：
        //定义两个指针，首先令其中一个指针 p1 向前走 n 步，然后让两个指针同步向前走，直到 p1 指向空结点，返回指针 p2 
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
    // 题目描述：
        //输入：链表1，链表2
        //返回：一个升序链表
    // 解题思路：
        // 用两个指针指向两条链表，创建虚拟头节点，遍历两条链表，通过比大小构造一条新链表
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        //定义两个指针
        ListNode* p1 = list1;
        ListNode* p2 = list2;

        //定义一个虚拟头节点
        ListNode* dummy = new ListNode(-1);

        //创建的链表的尾结点
        ListNode* p = dummy;

        // 注意点1：循环判定条件是两个指针同时不为空
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

        // 注意点2：退出循环后，要注意把长链表没有遍历到的结点拼接到新链表末端
        if (p1 != nullptr) {
                p->next = p1;
        } else {
                p->next = p2;
        }
        return dummy->next;
    }

    // 5.2 合并K个升序链表,循环形式
    // 题目描述：
        //输入：K个链表
        //返回:一个升序链表
    // 解题思路1：
        // 复用合并两条链表的函数，循环遍历每一条链表的头节点，不断把类一条链表加到新链表尾部；
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
    // 5.3 合并K个升序链表,递归形式
    // 解题思路2：
        // 复用合并两条链表的函数，递归遍历没一个链表的头节点
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

    // 5.4 合并K个升序链表，递归形式,平衡递归树，减少链表的重复遍历次数，提高算法的效率
        // 解题思路3：
    // 函数定义：
        // 输入：链表头节点数组，要合并的链表的起始头节点索引， 要合并的链表的末尾头节点索引
        // 返回：合并后的链表的头节点
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

// 6.反转链表
// 题目描述：
    // 给你一个链表的头节点，返回链表反转后的头节点
// 解题思路：定义一个递归函数：
    // 输入：一个链表的头节点
    // 返回：反转之后的链表的头节点
// 核心代码：
ListNode* reverseList(ListNode* head) {

    // 注意点1：这里判断条件是或的关系
    // base case
    if (head == nullptr || head->next == nullptr) return head;

    // 注意点2：这里返回的是头节点
    ListNode* last = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;

    return last;

}

// 7.随机链表的复制
// 题目描述：
    // 给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。 构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。返回复制链表的头节点。用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：val：一个表示 Node.val 的整数。random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。你的代码 只 接受原链表的头节点 head 作为传入参数。
// 解题思路：
    // 用一个哈希表存储原始链表和新链表之间的映射关系，遍历两次初始链表，第一次遍历，先把所有节点克隆出来；第二次遍历，把克隆结点的结构连接好，最后返回克隆之后的头节点
// 核心代码：
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> originToClone;

        // 第一次遍历：先把所有节点克隆出来
        for (Node* p = head; p != nullptr; p = p->next) {
            originToClone[p] = new Node(p->val);
        }

        // 第二次遍历：构造克隆结点的结构
        for (Node* p = head; p != nullptr; p = p->next) {
            // 注意点1：当前克隆节点应该指向下一个新的克隆结点，而不是原结点
            originToClone[p]->next = originToClone[p->next];
            originToClone[p]->random = originToClone[p->random];
        }

        return originToClone[head];
    }
};