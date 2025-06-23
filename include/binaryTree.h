//声明二叉树类的变量和方法
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <string>
using namespace std;

class BinaryTree {
private:
    struct Node {
        int val;
        Node* left;
        Node* right;
        Node* next;
        Node(int x);
    };

    //二叉树根节点
    Node* root;

    //二叉树遍历到的节点的深度
    int depth = 0;

    //二叉树的最大深度
    int maxdepth = 0; 

    //二叉树的最大直径
    int maxdiameter = 0;

    //二叉树的前序遍历结果，递归思路
    vector<int> preordertraversal;

    //返回二叉树前序遍历结果，分治思路
    vector<int> preOrderTraversal(Node* root);

    //递归遍历二叉树
    void traverse(Node* root);

    //统计二叉树节点数目
    int countInside(Node* root);

    //计算二叉树最大深度
    int maxDepth1(Node* root);
    int maxDepth2(Node* root);

    //计算二叉树直径 
    int diameterOfBinaryTree(Node* root);

    //二叉树展开为链表
    void flatten(Node* root);

    //填充每一个结点的下一个右侧结点的指针
    Node* connect(Node* root);

    // 返回二叉树的序列化字符串
    string serialize(Node* root);

    // 寻找重复的子树
    vector<Node*> findDuplicateSubtrees(Node* root);

    // 记录所有子树的序列化结果,以及出现次数
    unordered_map<string, int> subTrees;

    // 记录重复的子树根节点
    vector<Node*> duplicateSubtreesRoot;

public:
    //二叉树对象构造函数
    BinaryTree();

    //输入一个数组，创建一颗二叉树
    void buildBinaryTree1(vector<int>& values);

    //构造最大二叉树辅助函数
    Node* build1 (vector<int>& nums, int lo, int hi);

    //输入一个数组，按照最大二叉树原则，递归地构建一棵二叉树
    Node* constructMaximumBinaryTree(vector<int>& nums);

    // 存储 inorder 中值到索引的映射
    unordered_map<int, int> valToIndex;

    //根据前序遍历和中序遍历构造二叉树辅助函数
    Node* build2(vector<int> preorder, int preStart, int preEnd,
                 vector<int> inorder, int inStart, int inEnd);

    Node* buildBinaryTree2(vector<int> preorder, vector<int>& inorder);

    //根据中序遍历和后序遍历结果构造二叉树，辅助函数
    Node* build3(vector<int>& inorder, int inStart, int inEnd,
                 vector<int>& postorder, int postStart, int postEnd);

    Node* buildBinaryTree3(vector<int>& inorder, vector<int>& postorder);

    //根据前序遍历和后序遍历构造二叉树，辅助函数
    Node* build4(vector<int> preorder, int preStart, int preEnd,
                 vector<int>& postorder, int postStart, int postEnd);
    
    //根据前序遍历和后序遍历构造二叉树，存在多个答案可以返回任何一个
    Node* buildBinaryTree4(vector<int>& preorder, vector<int>& postorder);

    //二叉树的层序遍历
    vector<vector<int>> levelOrder();

    //二叉树的递归遍历
    void traverse();

    //返回二叉树结点数目
    int count();

    //返回二叉树的最大深度
    int maxDepth();

    //返回二叉树前序遍历结果
    vector<int> PreOrderTraversal();

    //返回二叉树的直径
    int diameterOfBinaryTree();

    //三叉树遍历框架
    void TernaryTreeTraversal (Node* node1, Node* node2);
};

// 力扣的二叉树节点的定义
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}; 
};

// 二叉树序列化的类
class Codec {
public: 
    // 定义分隔符,用于分开每个节点
    string SEP = ",";

    //定义空指针，用于标记 NULL
    string NULLSYM = "#";

    // 把一颗二叉树序列化成字符串,遍历方法实现
    string serializeTraverse(TreeNode* root);
    void _serializeTraverse(TreeNode* root, string& sb);

    // 把字符串反序列化成二叉树,遍历方法实现
    TreeNode* deserializeTraverse(string data);
    TreeNode* _deserializeTraverse(list<string>& nodes);
};

// 二叉搜索树的类
class BinarySearchTree {
public:
    // 当前节点的排名
    int rank = 0;

    // 第 K 小的元素
    int res = 0;

    // 累加和
    int sum = 0;

    // 二叉搜索树中第 K 小的元素
        // 给定一个二叉搜索树的根节点 root ，和一个整数 k ，
        // 请你设计一个算法查找其中第 k 小的元素（从 1 开始计数）。
    int kthSmallest(TreeNode* root, int k);
    void traverse(TreeNode* root, int k);

    // 二叉搜索树转换为累加树
        // 给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），
        // 使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。
    TreeNode* convertBST(TreeNode* root);
    void traverse2(TreeNode* root);
};

#endif // BINARY_TREE_H
