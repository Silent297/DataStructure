#include "../include/HuffmanTree.h"

// 构造函数
HuffmanTreeNode::HuffmanTreeNode(char ch, int freq) : character(ch), frequency(freq) {
    left = right = nullptr;
}

// 重写 getValue 方法，返回字符
string HuffmanTreeNode::getValue() {
    return string(1, character);  // 返回字符
}

// 获取节点频率
int HuffmanTreeNode::getFrequency() const {
    return frequency;
}

// 构建哈夫曼树
HuffmanTreeNode* HuffmanTreeNode::buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    // 创建最小堆
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, freq_cmp> minHeap;

    // 将所有字符和频率加入堆中
    // TODO
    for(auto it = freqMap.begin(); it != freqMap.end(); it++){
        HuffmanTreeNode* root = new HuffmanTreeNode;
        root->character = it->first;
        root->frequency = it->second;
        root->left = nullptr;
        root->right = nullptr;
        minHeap.push(root);
    }
    
    // 合并最小的两个节点，直到堆中只剩下一个节点
    // TODO
    while(minHeap.size() > 1){
        HuffmanTreeNode* left = minHeap.top();
        minHeap.pop();
        HuffmanTreeNode* right = minHeap.top();
        minHeap.pop();
        HuffmanTreeNode* root = new HuffmanTreeNode;
        root->left = left;
        root->right = right;
        root->frequency = left->frequency + right->frequency;
        root->character = '\0';
        minHeap.push(root);
    }

    // 返回哈夫曼树的根节点
    if(minHeap.size() == 1)
        return minHeap.top();
    else
        return nullptr;
}

// 打印哈夫曼树的编码（先序遍历）
void HuffmanTreeNode::printHuffmanCodes(HuffmanTreeNode* root, string code) {
    // TODO
    if(root == nullptr)
        return;
    if(root->character != '\0'){
        cout << root->character << ':';
        cout << code <<endl;
    }
    else{
        printHuffmanCodes(static_cast<HuffmanTreeNode*>(root->left), code+'0');
        printHuffmanCodes(static_cast<HuffmanTreeNode*>(root->right), code+'1');
    }
}
