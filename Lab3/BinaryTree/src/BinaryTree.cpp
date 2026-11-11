#include "../include/BinaryTree.h"
#include <iostream>
#include <queue>

using namespace std;

// 构造函数的实现，初始化左右孩子为 nullptr
BinaryTreeNode::BinaryTreeNode() : left(nullptr), right(nullptr) {}

// 先序遍历的实现：访问根节点，然后先序遍历左子树，再先序遍历右子树
void BinaryTreeNode::PreOrderTraverse(BinaryTreeNode* root) {
    // 使用getValue()函数获得节点的值
    // TODO
    if(root != nullptr){
        cout << root->getValue();
        PreOrderTraverse(root->left);
        PreOrderTraverse(root->right);
    }
}

// 中序遍历的实现：先中序遍历左子树，再访问根节点，最后中序遍历右子树
void BinaryTreeNode::InOrderTraverse(BinaryTreeNode* root) {
    if(root != nullptr){
        InOrderTraverse(root->left);
        cout << root->getValue();
        InOrderTraverse(root->right);
    }// TODO
}

// 后序遍历的实现：先后序遍历左子树，再后序遍历右子树，最后访问根节点
void BinaryTreeNode::PostOrderTraverse(BinaryTreeNode* root) {
    if(root != nullptr){
        PostOrderTraverse(root->left);
        PostOrderTraverse(root->right);
        cout << root->getValue();
    }
    // TODO
}

// 层次遍历的实现：使用队列，按层级从上到下、从左到右遍历树
void BinaryTreeNode::LevelOrderTraverse(BinaryTreeNode* root) {
    // TODO
    queue<BinaryTreeNode*> nodes;
    nodes.push(root);
    BinaryTreeNode *cur = nullptr;

    while(nodes.empty() == false){
        cur = nodes.front();
        nodes.pop();
        if(cur != nullptr){
        cout << cur->getValue();
            nodes.push(cur->left);
            nodes.push(cur->right);
        }
    }
}

// 辅助函数：通过中序和后序遍历构建树（递归实现）
BinaryTreeNode* BinaryTreeNode::buildTreeFromInorderPostorderHelper(const std::vector<std::string>& inorder, int inStart, int inEnd,
                                                                const std::vector<std::string>& postorder, int postStart, int postEnd,
                                                                    std::unordered_map<std::string, int>& inorderMap) {
    // 递归终止条件
    // TODO
    if(inEnd < inStart){
        return nullptr;
    }

    // 后序遍历的最后一个元素是根节点
    // TODO
    BinaryTreeNode* root = new BinaryTreeNode;
    root->name = postorder[postEnd];

    // 获取根节点在中序遍历中的位置并计算左子树的大小
    // TODO
    int root_pos = inorderMap[root->name];
    int length = root_pos - inStart;

    // 递归构建左子树和右子树
    // TODO
    root->left = buildTreeFromInorderPostorderHelper(inorder, inStart, inStart + length - 1, 
                                                    postorder, postStart, postStart + length - 1, inorderMap);
    root->right = buildTreeFromInorderPostorderHelper(inorder, inStart + length + 1, inEnd, 
                                                    postorder, postStart + length, postEnd - 1, inorderMap);
    return root;
}

// 构建树的函数，调用辅助函数来构建二叉树
BinaryTreeNode* BinaryTreeNode::buildTreeFromInorderPostorder(const std::vector<std::string>& inorder, const std::vector<std::string>& postorder) {
    std::unordered_map<std::string, int> inorderMap;
    // 构建中序遍历值到索引的映射，方便快速查找
    for (size_t i = 0; i < inorder.size(); ++i) {
        inorderMap[inorder[i]] = i;
    }

    // 调用辅助函数开始构建树
    return buildTreeFromInorderPostorderHelper(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1, inorderMap);
}

// 辅助函数：通过中序和前序遍历构建树（递归实现）
BinaryTreeNode* BinaryTreeNode::buildTreeFromInorderPreorderHelper(const vector<string>& inorder, int inStart, int inEnd, 
                                                                     const vector<string>& preorder, int preStart, int preEnd, 
                                                                     unordered_map<string, int>& inorderMap) {
    // 递归终止条件
    // TODO
    if(inEnd < inStart){
        return nullptr;
    }           

    // 前序遍历的第一个元素是根节点
    // TODO
    BinaryTreeNode* root = new BinaryTreeNode;
    root->name = preorder[preStart];

    // 获取根节点在中序遍历中的位置并计算左子树的大小
    // TODO
    int root_pos = inorderMap[root->name];
    int length = root_pos - inStart;


    // 递归构建左子树和右子树
    // TODO
    root->left = buildTreeFromInorderPreorderHelper(inorder, inStart, inStart + length - 1, 
                                                    preorder, preStart + 1, preStart + length, inorderMap);
    root->right = buildTreeFromInorderPreorderHelper(inorder, inStart + length + 1, inEnd, 
                                                    preorder, preStart + length + 1, preEnd, inorderMap);
    return root;
    
}

// 构建树的函数，调用辅助函数来构建二叉树
BinaryTreeNode* BinaryTreeNode::buildTreeFromInorderPreorder(const vector<string>& inorder, const vector<string>& preorder) {
    unordered_map<string, int> inorderMap;
    // 构建中序遍历值到索引的映射
    for (size_t i = 0; i < inorder.size(); ++i) {
        inorderMap[inorder[i]] = i;
    }

    // 调用辅助函数开始构建树
    return buildTreeFromInorderPreorderHelper(inorder, 0, inorder.size() - 1, preorder, 0, preorder.size() - 1, inorderMap);
}

// getValue 虚函数的实现，返回当前节点的名字
string BinaryTreeNode::getValue() {
    return this->name;
}
