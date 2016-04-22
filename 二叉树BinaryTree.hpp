#define _CRT_SECURE_NO_WARNINGS 1

#include "BinaryTree.h"

template <typename T>
BinaryTree<T>::BinaryTree() :_root(NULL)
{}

template <typename T>
BinaryTree<T>::BinaryTree(const T* array, size_t size, const T& invalid) : _root(NULL)
{
	size_t index = 0;
	this->_root = _CreateTree(array, size, invalid, index);
}

template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::_CreateTree(const T* array, const size_t& size, const T& invalid, size_t& index)
{
	assert(array);
	BinaryTreeNode<T>* node = NULL;
	if (index < size && array[index] != invalid)
	{
		node = new BinaryTreeNode<T>(array[index]);
		node->_left = _CreateTree(array, size, invalid, ++index);
		node->_right = _CreateTree(array, size, invalid, ++index);
	}
	return node;
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& tree)
{
	this->_root = this->_Copy(tree._root);
}

//template <typename T>
//BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& tree)
//{
//	if (this != &tree)
//	{
//		Node* node = _Copy(tree._root);
//		this->~BinaryTree();
//		this->_root = node;
//	}
//	return *this;
//}

template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree<T> tree)
{
	swap(this->_root, tree._root);

	return *this;
}

template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::_Copy(BinaryTreeNode<T>* root)
{
	Node* node = NULL;
	if (root)
	{
		node = new Node(root->_data);
		node->_left = _Copy(root->_left);
		node->_right = _Copy(root->_right);
	}
	return node;
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
	this->_Destroy(this->_root);
}

template <typename T>
void BinaryTree<T>::_Destroy(BinaryTreeNode<T>* root)
{
	if (root)
	{
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}
}

template <typename T>
void BinaryTree<T>::PrevOrder()const
{
	this->_PrevOrder(this->_root);
	cout << endl;
}

template <typename T>
void BinaryTree<T>::_PrevOrder(BinaryTreeNode<T>* root)const
{
	if (root)
	{
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
}

template <typename T>
void BinaryTree<T>::InOrder()const
{
	this->_InOrder(this->_root);
	cout << endl;
}

template <typename T>
void BinaryTree<T>::_InOrder(BinaryTreeNode<T>* root)const
{
	if (root)
	{
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}
}

template <typename T>
void BinaryTree<T>::PostOrder()const
{
	this->_PostOrder(this->_root);
	cout << endl;
}

template <typename T>
void BinaryTree<T>::_PostOrder(BinaryTreeNode<T>* root)const
{
	if (root)
	{
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}
}

template <typename T>
void BinaryTree<T>::LevelOrder()const
{
	if (this->_root == NULL)
	{
		return;
	}
	queue<Node*> qTree;
	qTree.push(this->_root);
	while (!qTree.empty())
	{
		Node* front = qTree.front();
		cout << front->_data << " ";
		if (front->_left)
		{
			qTree.push(front->_left);
		}
		if (front->_right)
		{
			qTree.push(front->_right);
		}
		qTree.pop();
	}
}

template <typename T>
size_t BinaryTree<T>::Size()const
{
	size_t size = this->_Size(this->_root);
	return size;
}

template <typename T>
size_t BinaryTree<T>::_Size(Node* root)const
{
	if (root == NULL)
	{
		return 0;
	}
	return _Size(root->_left) + _Size(root->_right) + 1;
}

template <typename T>
size_t BinaryTree<T>::Depth()const
{
	size_t depth = this->_Depth(this->_root);
	return depth;
}

template <typename T>
size_t BinaryTree<T>::_Depth(Node* root)const
{
	if (root == NULL)
	{
		return 0;
	}
	size_t left = _Depth(root->_left) + 1;
	size_t right = _Depth(root->_right) + 1;
	return left > right ? left : right;
}

template <typename T>
size_t BinaryTree<T>::LeafSize()const
{
	size_t leftSize = this->_LeafSize(this->_root);
	return leftSize;
}

template <typename T>
size_t BinaryTree<T>::_LeafSize(Node* root)const
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->_left == NULL&&root->_right == NULL)
	{
		return 1;
	}
	return _LeafSize(root->_left) + _LeafSize(root->_right);
}

template <typename T>
void  BinaryTree<T>::ExchangeLeftRight()
{
	this->_ExChangLR(this->_root);
}

template <typename T>
void  BinaryTree<T>::_ExChangLR(BinaryTreeNode<T>* root)
{
	if (root == NULL)
	{
		return;
	}
	if (root->_left == NULL && root->_right == NULL)
	{
		return;
	}
	swap(root->_left, root->_right);
	_ExChangLR(root->_left); 
	_ExChangLR(root->_right);
}

template <typename T>
void BinaryTree<T>::PrevOrderNRed()const
{
	if (this->_root == NULL)
	{
		return;
	}
	stack<Node*> s;
	s.push(this->_root);
	while (!s.empty())
	{
		Node* top = s.top();
		cout << top->_data << " ";
		s.pop();
		if (top->_right)
		{
			s.push(top->_right);
		}
		if (top->_left)
		{
			s.push(top->_left);
		}
	}
	cout << endl;
}

template <typename T>
void BinaryTree<T>::InOrderNRed()const
{
	if (this->_root == NULL)
	{
		return;
	}
	stack<Node*> s;
	Node* cur = this->_root;
	while (cur || !s.empty())
	{
		while (cur)
		{
			s.push(cur);
			cur = cur->_left;
		}
		if (!s.empty())
		{
			Node* top = s.top();
			cout << top->_data << " ";
			s.pop();
			cur = top->_right;
		}
	}
	cout << endl;
}

template <typename T>
void BinaryTree<T>::PostOrderNRed()const
{
	if (this->_root == NULL)
	{
		return;
	}
	stack<Node*> s;
	Node* cur = this->_root;
	Node* prev = NULL;
	while (cur || !s.empty())
	{
		while (cur)
		{
			s.push(cur);
			cur = cur->_left;
		}
		Node* top = s.top();
		if (top->_right == NULL || top->_right == prev)
		{
			cout << top->_data << " ";
			s.pop();
			prev = top;
		}
		else
		{
			cur = top->_right;
		}
	}
	cout << endl;
}

template <typename T>
size_t BinaryTree<T>::GetLevelKNRed(int k)const
{
	assert(k > 0);
	if (this->_root == NULL)
	{
		return 0;
	}
	queue<Node*> q;
	q.push(this->_root);
	for (int i = 1; i < k; ++i)
	{
		size_t size = q.size();
		for (int j = 0; j < size; ++j)
		{
			Node* front = q.front();
			if (front->_left)
			{
				q.push(front->_left);
			}
			if (front->_right)
			{
				q.push(front->_right);
			}
			q.pop();
		}
	}
	return q.size();
}

template <typename T>
size_t BinaryTree<T>::GetLevelK(int k)const
{
	if (this->_root == NULL)
	{
		return 0;
	}
	return _GetLevelK(this->_root, k);
}

template <typename T>
size_t BinaryTree<T>::_GetLevelK(Node* root, int k)const
{
	if (root == NULL)
	{
		return 0;
	}
	if (k == 1)
	{
		return 1;
	}
	return _GetLevelK(root->_left, k - 1) + _GetLevelK(root->_right, k - 1);
}

template <typename T>
void BinaryTreeThd<T>::InThreadedNRec()
{
	if (this->_root == NULL)
	{
		return;
	}
	Node* cur = this->_root;
	Node* prev = NULL;
	stack<Node*> s;
	while (cur || !s.empty())
	{
		while (cur)
		{
			s.push(cur);
			cur = cur->_left;
		}
		Node* top = s.top();
		if (!s.empty())
		{
			//cout << top->_data << " ";
			if (top->_left == NULL)
			{
				top->_left = prev;
				top->_leftTag = THREAD;
			}
			if (prev && prev->_right == NULL)
			{
				prev->_right = top;
				prev->_rightTag = THREAD;
			}
			prev = top;
			s.pop();
			cur = top->_right;
		}
	}
	cout << endl;
}
