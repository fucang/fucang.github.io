#pragma once
#ifndef __RBTREE_H__
#define __RBTREE_H__

#include <iostream>
using namespace std;

/*
*红黑树：
*性质1. 节点是红色或黑色。
*性质2. 根节点是黑色。
*性质3 每个叶节点（NIL节点，空节点）是黑色的。
*性质4 每个红色节点的两个子节点都是黑色。(从每个叶子到根的所有路径上不能有两个连续的红色节点)
*性质5. 从任一节点到其每个叶子的所有路径都包含相同数目的黑色节点。
*/
/*
*因为第1条该树上的节点非红即黑，由于第4条该树上不允许存在两个连续的红节点，那么对于从一个节点
*到其叶子节点的一条最长的路径一定是红黑交错的，那么最短路径一定是纯黑色的节点；而又第5条从任
*一节点到其叶子节点的所有路径上都包含相同数目的黑节点，这么来说最长路径上的黑节点的数目和最短
*路径上的黑节点的数目相等！而又第2条根结点为黑、第3条叶子节点是黑，那么可知：最长路径<=2*最短路径。
*/

enum Color
{
	RED,
	BLACK,
};

template <typename K,typename V>
struct RBTreeNode
{
	Color _col;
	K _key;
	V _value;
	RBTreeNode<K, V>* _parent;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode(const K key = K(), const V value = V())
		:_col(RED), _key(key), _value(value)
		, _parent(NULL), _left(NULL), _right(NULL)
	{}
};

template <typename K,typename V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree();
	bool Insert(const K& key, const V& value = V());

protected:
	void _RolateL(Node* &parent);
	void _RolateR(Node* &parent);
protected:
	Node* _root;
};

#endif /*__RBTREE_H__*/
