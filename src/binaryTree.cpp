//定义二叉树类的方法
#include "../include/binaryTree.h"
#include <queue>
#include <iostream>
using namespace std;

//Node构造函数实现（注意作用域！）
BinaryTree::Node::Node(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}

//二叉树类构造函数
BinaryTree::BinaryTree() : root(nullptr) {}

//通过一个数组，创建一棵二叉树
    //输入：数组
    //返回：无
void BinaryTree::buildBinaryTree1(vector<int>& values) {

    //数组为空，直接返回
    if (values.empty()) return;

    //数组的第一个元素是二叉树的根节点
    root = new Node(values[0]);

    //初始化一个队列，存储已经成为二叉树一部分的结点
    queue<Node*> q;

    //根节点入队列
    q.push(root);

    //数组的下一个元素的索引
    size_t i = 1;

    while (!q.empty() && i < values.size()) {

        Node* cur = q.front(); q.pop();

        //-1表示当前节点为空
        //先左子树
        if (values[i] != -1) {
            cur->left = new Node(values[i]);
            q.push(cur->left);
        }

        i++;

        //后右子树
        if (i < values.size() && values[i] != -1) {
            cur->right = new Node(values[i]);
            q.push(cur->right);
        }

        i++;
    }
}

//构造最大二叉树辅助函数
    //输入：数组，低索引，高索引
    //返回：最大二叉树的根节点
BinaryTree::Node* BinaryTree:: build1(vector<int>& nums, int lo, int hi) {
    //base case
    if (lo > hi) return nullptr;

    //找到数组中最大值和对应的索引
    int index = -1, maxVal = INT_MIN;
    for (int i = lo; i <= hi; i++) {
        if (maxVal < nums[i]) {
            maxVal = nums[i];
            index = i;
        }
    }

    //先构造根节点
    Node* root = new Node(maxVal);

    //递归的构造左右子树
    root->left = build1(nums, lo, index-1);
    root->right = build1(nums, index+1, hi);

    return root;
}

//输入一个数组，按照最大二叉树原则：
    //1.创建一个根节点，其值为 nums 中的最大值。
    //2.递归地在最大值左边的子数组前缀上构建左子树。
    //3.递归地在最大值右边的子数组后缀上构建右子树。          
    //输入：数组
    //返回：二叉树根节点
BinaryTree::Node* BinaryTree::constructMaximumBinaryTree(vector<int>& nums) {
    if (nums.empty()) return nullptr;
    return build1(nums, 0, nums.size()-1);
}

//根据前序遍历和中序遍历构造二叉树辅助函数
    //输入：前序/中序遍历数组，起始索引，末尾索引
    //返回：二叉树根节点
BinaryTree::Node* BinaryTree::build2(vector<int> preorder, int preStart, int preEnd,
                 vector<int> inorder, int inStart, int inEnd) {
     //base case
     if (preStart > preEnd) {
        return nullptr;
     }

     //root的值是preorder中的第一个元素
     int rootVal = preorder[preStart];

     //rootVal在inorder中的索引
     int index = valToIndex[rootVal];

     //左子树的长度
     int leftSize = index - inStart;

     //先构造根节点
     Node* root = new Node(rootVal);

     //递归构造左子树
     root->left = build2(preorder, preStart+1, preStart+leftSize, 
                        inorder, inStart, index-1);

     //递归构造右子树
     root->right = build2(preorder, preStart+leftSize+1, preEnd,
                         inorder, index+1, inEnd);

     return root;
}

BinaryTree::Node* BinaryTree::buildBinaryTree2(vector<int> preorder, vector<int>& inorder) {
    //建立inorder中值到索引的映射，可以减少循环的次数
    int sz = inorder.size();
    for (int i = 0; i < sz; i++) {
        valToIndex[inorder[i]] = i;
    }

    return build2(preorder, 0, preorder.size()-1, 
                  inorder, 0, inorder.size()-1);
}

//根据中序遍历和后序遍历构造二叉树辅助函数
    //输入：中序/后序遍历数组，起始索引，末尾索引
    //返回：二叉树根节点
BinaryTree::Node* BinaryTree::build3(vector<int>& inorder, int inStart, int inEnd,
                                     vector<int>& postorder, int postStart, int postEnd) {
    //base case
    if (postStart > postEnd) {
        return nullptr;
    }

    //root的值是postorder中最后一个元素
    int rootVal = postorder[postEnd];
    
    //rootVal在inorder中的索引
    int index = valToIndex[rootVal];

    //右子树的长度
    int rightSize = inEnd - index;

    //先构造根节点
    Node* root = new Node(rootVal);

    //递归构造左子树
    root->left = build3(inorder, inStart, index-1,
                        postorder, postStart, postEnd-rightSize-1);

    //递归构造右子树
    root->right = build3(inorder, index+1, inEnd,
                         postorder, postEnd-rightSize, postEnd-1);

    //返回根节点
    return root;

}

BinaryTree::Node* BinaryTree::buildBinaryTree3(vector<int>& inorder, vector<int>& postorder) {
    //建立inorder中值到索引的映射，可以减少循环的次数
    int sz = inorder.size();
    for (int i = 0; i < sz; i++) {
        valToIndex[inorder[i]] = i;
    }

    return build3(inorder, 0, inorder.size()-1,
                  postorder, 0, postorder.size()-1);
}

//根据前序遍历和后序遍历构造二叉树，辅助函数
    //输入：前/后序遍历，起始/结尾索引
    //返回：二叉树根节点
    //构造原则：
        //1.首先把前序遍历结果的第一个元素确定为根节点的值。
        //2.然后把前序遍历结果的第二个元素作为左子树的根节点的值。
        //3.在后序遍历结果中寻找左子树根节点的值，从而确定了左子树的索引边界，进而确定右子树的索引边界，递归构造左右子树即可。
BinaryTree::Node* BinaryTree::build4(vector<int> preorder, int preStart, int preEnd,
                                     vector<int>& postorder, int postStart, int postEnd) {
    //base case
    if (preStart > preEnd) return nullptr;
    
    //当 preorder 只剩一个节点时，preorder[preStart + 1] 会越界
    if (preStart == preEnd) {
        return new Node(preorder[preStart]);
    }

    //root的值是preorder中第一个元素
    int rootVal = preorder[preStart];

    //root.left的值是前序遍历第二个元素
    int leftRootVal = preorder[preStart+1];
    
    //leftRootVal 在后序遍历数组中的索引
    int index = valToIndex[leftRootVal];

    //左子树的元素数目
    int leftSize = index - postStart + 1;

    //先构造出当前根节点
    Node* root = new Node(rootVal);

    // 递归构造左右子树
    // 根据左子树的根节点索引和元素个数推导左右子树的索引边界
    root->left = build4(preorder, preStart+1, preStart+leftSize,
                        postorder, postStart, index);
    // 这里 postEnd 应该是 postEnd - 1，因为 postorder[postEnd] 是当前根节点，不属于右子树
    root->right = build4(preorder, preStart+leftSize+1, preEnd,
                         postorder, index+1, postEnd-1);
    
    return root;
}

//根据前序遍历和后序遍历构造二叉树
    //输入：前/后序遍历
    //返回：二叉树根节点
BinaryTree::Node* BinaryTree:: buildBinaryTree4(vector<int>& preorder, vector<int>& postorder) {
    //建立postorder中值到索引的映射，可以减少循环的次数
    int sz = postorder.size();
    for (int i = 0; i < sz; i++) {
        valToIndex[postorder[i]] = i;
    }

    return build4(preorder, 0, preorder.size()-1,
                  postorder, 0, postorder.size()-1);
}





//二叉树的层序遍历
    //输入：无
    //返回：二维数组
vector<vector<int>> BinaryTree::levelOrder() {

    //存储返回的结果，数组的每行表示二叉树的一层
    vector<vector<int>> res;

    //增强鲁棒性
    if (!root) return res;

    //存储叶子节点的队列
    queue<Node*> q;

    //根节点压入队列
    q.push(root);

    //根节点在第一层
    int depth = 1;

    while (!q.empty()) {

        //当前层中叶子节点的数量
        int sz = q.size();

        //存储当前层中所有的叶子节点
        vector<int> level;

        for (int i = 0; i < sz; i++) {

            //出队列
            Node* node = q.front(); q.pop();

            cout << "depth = " << depth << " " << node->val << endl;

            //压入当前层
            level.push_back(node->val);

            //将当前叶子结点下一层的左右子树入队列
                //注意：子节点入队前判断是否为空
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        //一层遍历完后，压入结果数组
        res.push_back(level);

        //层数加一
        depth++;
    }

    return res;
}

//二叉树的递归遍历
    //输入：无
    //返回：无
void BinaryTree::traverse(Node* root) {
    if (!root) return;
    //前序遍历
    // cout << root->val << endl;

    //前序遍历位置，进入结点，增加深度
    depth++;

    //前序遍历位置加入结点
    preordertraversal.push_back(root->val);

    //遍历到叶子结点时，记录最大深度
    if (root->left == nullptr && root->right == nullptr) {
        maxdepth = max(depth, maxdepth);
    }

    traverse(root->left);
    //中序遍历
    // cout << root->val << endl;
    traverse(root->right);
    //后序遍历
    // cout << root->val << endl;

    //后续位置，离开结点，减小深度
    depth--;
}

void BinaryTree::traverse() {
    traverse(root); // 调用私有递归方法
}

//统计二叉树结点数目，分解思路
    //输入：二叉树根节点
    //返回：二叉树节点数目
int BinaryTree::countInside(Node* root) {
    //base case
    if (!root) return 0;

    //计算左子树节点数目
    int leftreeNum = countInside(root->left);

    //计算右子树节点数目
    int rightreeNum = countInside(root->right);

    return leftreeNum + rightreeNum + 1;
}

int BinaryTree::count() {
    return countInside(root);
}

//返回二叉树的最大深度:分治问题的思路解法
//递归函数定义：
    //输入：二叉树根节点
    //返回：二叉树的最大深度
int BinaryTree::maxDepth1(Node* head) {
    //base case
    if (!head) return 0;

    //计算左子树的最大深度
    int lefMaxDepth = maxDepth1(head->left);

    //计算右子树的最大深度
    int righMaxDepth = maxDepth1(head->right);

    //计算并更新二叉树的最大直径
    int cur = lefMaxDepth + righMaxDepth;
    maxdiameter = max(maxdiameter, cur);

    //最大深度 = 左/右子树最大深度 + 根节点
    return max(lefMaxDepth, righMaxDepth) + 1;
}

//返回二叉树的最大深度：遍历的思路
int BinaryTree::maxDepth2(Node* root) {
    traverse(root);
    return maxdepth;
}


//返回二叉树的最大深度，外部调用
int BinaryTree::maxDepth() {
    // return maxDepth1(root);
    return maxDepth2(root);
}

//返回二叉树的前序遍历结果,分解问题思路
//递归函数的定义：
    //输入：二叉树根节点
    //返回：二叉树的前序遍历结果
vector<int> BinaryTree::preOrderTraversal(Node* root) {
    //初始化返回数组
    vector<int> res;

    //base case
    if (root == nullptr) return res;

    //根节点压入返回数组
    res.push_back(root->val);

    //左子树前序遍历结果
    vector<int> leftPre = preOrderTraversal(root->left);

    //右子树前序遍历结果
    vector<int> rightPre = preOrderTraversal(root->right);

    //合并结果
    res.insert(res.end(), leftPre.begin(), leftPre.end());
    res.insert(res.end(), rightPre.begin(), rightPre.end());

    //返回结果
    return res;
}

//返回二叉树前序遍历结果，外部调用接口
vector<int> BinaryTree::PreOrderTraversal() {
    //思路一：遍历
    // traverse(root);
    // return preordertraversal;

    //思路二：分解
    return preOrderTraversal(root);
}

//计算二叉树的直径
    //输入：二叉树根节点
    //返回：二叉树直径
int BinaryTree::diameterOfBinaryTree(Node* root) {
    maxDepth1(root);
    return maxdiameter;
}

//外部接口
int BinaryTree:: diameterOfBinaryTree() {
    return diameterOfBinaryTree(root);
}

//三叉树遍历
    //输入：二叉树的两个节点
    //返回：无
void BinaryTree::TernaryTreeTraversal(Node* node1, Node* node2) {
    //base case
    if (!node1 || !node2) return;

    // 将传入的两个结点连起来
    node1->next = node2;

    // 连接相同父结点的两个结点
    TernaryTreeTraversal(node1->left, node1->right);
    TernaryTreeTraversal(node2->left, node2->right);

    // 连接相邻结点
    TernaryTreeTraversal(node1->right, node2->left);
}

// 连接相邻结点的定义
    // 输入：二叉树根节点
    // 返回：二叉树根节点
BinaryTree::Node* BinaryTree:: connect(Node* root) {
    if (!root) return root;

    //遍历三叉树，连接相邻结点
    TernaryTreeTraversal(root->left, root->right);

    return root;
}

// 二叉树展开成链表,分解思路
    // 输入：二叉树根节点
    // 返回：无
    // 函数定义：输入二叉树根节点，二叉树展开成链表
void BinaryTree::flatten(Node* root) {
    // base case
    if (!root) return;

    // 先将左右子树各自展开成链表
    flatten(root->left);
    flatten(root->right);

    // 然后将展开的右子树接到左子树下方
    // 1.定义两条链表的头节点
    Node* leftList = root->left;
    Node* rightList = root->right;
    
    // 2.将左子树作为右子树
    root->right = leftList;
    root->left = nullptr;

    // 3.将原先右子树接到当前右子树末端
    Node* p = root;
    while(p->right) {    
        p = p->right;
    }
    p->right = rightList;
}

// 返回二叉树的序列化字符串
    // 输入：二叉树根节点
    // 返回：二叉树后序遍历字符串
string BinaryTree::serialize(Node* root) {
    // 空节点，用一个特殊字符表示
    if (!root) {
        return "#";
    }

    // 将左右子树序列化成字符串
    string left = serialize(root->left);
    string right = serialize(root->right);

    // 后序遍历代码位置
    // 左右子树加上自己，就是以自己为根的二叉树序列化结果
    string myself = left + "," + right + "," + to_string(root->val);

    //当前子二叉树序列出现的次数
    int freq = subTrees[myself];

    //多次重复也只会被加入结果集一次
    if (freq == 1) {
        duplicateSubtreesRoot.push_back(root);
    }

    // 给子树对应的出现次数加一
    subTrees[myself] = freq + 1;
    
    return myself;
}

// 寻找重复子树
    //输入：一棵二叉树的根节点 root
    //返回：所有重复的子树
    //注意：如果两棵树具有相同的结构和相同的结点值，则认为二者是重复的。
vector<BinaryTree::Node*> BinaryTree::findDuplicateSubtrees(Node* root) {
    serialize(root);
    return duplicateSubtreesRoot;
}


