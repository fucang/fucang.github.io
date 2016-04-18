#pragma once 
#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <assert.h>
#include <queue>

template <typename T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	BinaryTreeNode(const T& x = T()) :_data(x), _left(NULL), _right(NULL)
	{}
};

template <typename T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;

public:
	BinaryTree();
	BinaryTree(const T* array, size_t size, const T& invalid);
	BinaryTree(const BinaryTree<T>& tree);
	//BinaryTree<T>& operator=(const BinaryTree<T>& tree); //传统
	BinaryTree<T>& operator=(BinaryTree<T> tree); //现代
	~BinaryTree();
	void PrevOrder()const;
	void InOrder()const;
	void PostOrder()const;
	void LevelOrder()const;
	size_t Size()const;
	size_t Depth()const;
	size_t LeafSize()const;

protected:
	BinaryTreeNode<T>* _CreateTree(const T* array, const size_t& size, const T& invalid, size_t& index);
	Node* _Copy(Node* root);
	void _Destroy(Node* root);

	void _PrevOrder(Node* root)const;
	void _InOrder(Node* root)const;
	void _PostOrder(Node* root)const;
	void _LevelOrder(Node* root)const;
	size_t _Size(Node* root)const;
	size_t _Depth(Node* root)const;
	size_t _LeafSize(Node* root)const;

protected:
	Node* _root;
};

#endif /*__BINARY_TREE_H__*/
