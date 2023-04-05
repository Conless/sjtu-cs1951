---
title: 数据结构（三）：红黑树与 STL map
date: 2023/02/19 10:10:00
math: true
categories:
- [Computer Science, Data Structure (CS1951@SJTU)]
---
# 红黑树

红黑树是一种平衡树，其维持平衡的基本方式为保证每条路径上黑色节点的数量相同。

## 基础性质
1. 节点为红色或黑色
2. 空叶子节点（NIL）为黑色
3. 没有两个连续的红色节点
4. 从根到 NIL 的每条路径的黑色节点数量相同

## 结构
一个节点需要包含的信息
```cpp
enum color{ RED, BLACK };
struct tnode {
    tnode *left, *right, *parent;
    color col;
    Key key;
    T data;
};
```
整棵树需要储存的基本信息
```cpp
template <class Key, class T, class Compare = std::less<Key>> class key {
  private:
    tnode *rt;
    size_t siz;
  public:
    ...
};
```

## 操作
### 旋转

左旋是这样的：
```
  rt              r0
 /  \            /  \
l0   r0  ---->  rt  r1
    /  \       /  \
   l1  r1     l0  l1
```
实际上，就是做了个根和右儿子的交换，其它东西放在能放的位置。要求右儿子必须存在。

右旋是这样的
```
    rt             l0
   /  \           /  \
  l0  r0  ---->  l1  rt
 /  \               /  \
l1  r1             r1  r0
```
实际上，就是做了个根和左儿子的交换，其它东西放在能放的位置。要求左儿子必须存在。

### 插入

红黑树将新插入的节点初始化为红色节点，先按照正常 BST 的方式找到应该在哪里进行插入，此时，若父节点是黑色节点，显然没问题，若父节点 P 是非根的红色节点，分以下几种情况：
1. 当前节点的父节点 P 和叔节点 U 均为红色，这意味着祖父为黑，可以直接将祖父染红，P U 染黑
```
    BLACK             RED
   /    \            /   \
  RED   RED ----> BLACK BLACK
  /               /
<NEW>           <NEW>
```
此时有可能有一个新的问题：要是祖父节点染红导致了性质破坏（连续红色节点）怎么办？这个时候可以递归地向上跳，不断进行维护，使得这一性质始终满足。这是染色中相对简单的情况。

2. 当前节点的父节点 P 为红，但是叔节点 U 为黑或不存在，这个时候需要让新插入的节点在父节点的外侧节点上（如左儿子的外侧节点也为左儿子），如果不是的话，首先进行旋转操作：
- 父节点在左子树上，旋转为 LL 的情况。
```
    BLACK               BLACK
   /     \             /     \
  RED   BLACK ---->  <NEW>  BLACK
 /  \                /  \
A   <NEW>           RED  C
    /   \          /  \
   B     C        A    B
```
随后进行红黑树的 LLb 旋转，本质上就是父辈三个节点右旋
```
     BLACK                   RED
    /     \                /    \
   RED  BLACK            RED    BLACK
  /  \          ---->   /   \   /   \
 RED  C                A     B C    BLACK
 /  \
A    B
```
注意其中 ABC 均为黑色节点，所以此时黑色节点个数不再平衡，需要进行染色，这一步操作也不困难，将 RED - BLACK 的连线改为 BLACK - RED 即可。

- 父节点在右子树上，旋转为 RR 的情况。
```
      BLACK                 BLACK
     /     \               /     \
  BLACK    RED           BLACK   RED
          /   \   ---->         /   \
        <NEW>  A               C    <NEW>
        /   \                       /   \
       B     C                     B     A
```
随后进行红黑树的 RRb 旋转，本质就是父辈三个节点左旋
```
     BLACK                RED
    /     \             /     \
  BLACK  RED ---->   BLACK    RED
         /  \        /   \    /  \
        A   RED   BLACK   A  B    C
           /   \
          B     C
```
同理，将 RED - BLACK 连线改为 BLACK - RED。

### 删除


  