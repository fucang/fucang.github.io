#pragma once
#ifndef __BTREE_H__
#define __BTREE_H__

template <typename K,int M = 3>
struct BTreeNode
{
	K _keys[M];//最多存储M个数，多一个空间是为了方便分裂
	BTreeNode<K, M>* _subs[M + 1];//本来_subs[M],原因同_keys
	BTreeNode<K, M>* _parent;
	size_t _size;//_keys里面的有效数字可能小于M，所以用来存储_keys中的有效数字的个数
	BTreeNode() :_parent(NULL), _size(0)
	{
		for (int i = 0; i < M + 1; ++i)
		{
			this->_subs[i] = NULL;
		}
	}
};

template <typename K,int M = 3>
struct Pair
{
	typedef BTreeNode<K, M> Node;
	Node* _first;
	int _second;
	Pair(Node* first = NULL, int second = 0)
		:_first(first), _second(second)
	{}
};

template <typename K, int M = 3>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	BTree();
	bool Insert(const K& key);
	Pair<K,M> Find(const K& key)const;
	void InOrder()const;
	bool Delete(const K& key);
protected:
	void _InsertKey(Node* cur, const K& key);
	static void _InOrder(const Node* root, int index);

protected:
	Node* _root;
};

#endif /*__BTREE_H__*/
