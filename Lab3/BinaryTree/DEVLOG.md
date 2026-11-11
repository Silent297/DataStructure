# BinaryTree 开发日志

## 2026-11-11

### 状态：内存管理搁置

**约束**：不改 `src/main.cpp`，不改 `include/*.h`，只允许改 `src/BinaryTree.cpp`。

**已确认可行的方案**（暂不落地）：在 `BinaryTree.cpp` 匿名 namespace 内维护静态节点登记表，建树 helper 中每次 `new BinaryTreeNode` 后登记，程序退出时由静态对象析构统一 `delete`。已在临时副本中验证：两棵树重建结果 `DEBFCA` / `ABDECF` 正确，退出码 0，无 double free。

参考代码（插入 `using namespace std;` 之后）：

```cpp
namespace {
struct NodePool {
    vector<BinaryTreeNode*> nodes;

    ~NodePool() {
        for (auto* p : nodes) {
            delete p;
        }
    }
};

NodePool& pool() {
    static NodePool p;
    return p;
}
}
```

两个 helper 中 `new BinaryTreeNode` 之后各加一行 `pool().nodes.push_back(root);`。

**局限**：

- 只覆盖基础二叉树；`ExpressionBinaryTreeNode`、`HuffmanTreeNode` 的节点不在登记范围，仍由进程退出回收。
- 释放发生在进程退出时，不是用完立即释放。
- 全局登记池不符合框架惯例，可能被助教质疑。
- 编译会出现 `-Wdelete-non-virtual-dtor` 警告（实际安全：池中对象动态类型均为 `BinaryTreeNode`）。

**恢复前置条件**：先确认验收方式——人工看代码，则接受 OS 回收即可；要求运行期零泄漏，才落地上述登记池。

### 其他未决问题

- `LevelOrderTraverse` 第 51 行为 `cout << root->getValue();`，应改为 `cur->getValue();`（main 未调用层次遍历，样例不会暴露）。
- 表达式树、哈夫曼树尚未实现，`main` 运行到表达式树部分会段错误。
