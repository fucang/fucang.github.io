#define _CRT_SECURE_NO_WARNINGS 1

#include "RBTree.h"

template <typename K, typename V>
RBTree<K, V>::RBTree() :_root(NULL)
{}

/*
*插入的几种情况：
*情形1：该树为空树，直接插入根结点的位置，违反性质1，把节点颜色有红改为黑即可。
*情形2：插入节点N的父节点P为黑色，不违反任何性质，无需做任何修改。
*情形1很简单，情形2中P为黑色，一切安然无事，但P为红就不一样了，下边是P为红的各种情况：
*情形3：N为红，P为红，（祖节点一定存在，且为黑，下边同理）U也为红，这里不论P是G的左孩子，还是右孩子；不论N是P的左孩子，还是右孩子。
*	操作：把P、U改为黑色，G改为红色，未结束，因为可能导致上面两个红色结点连着，往上循环
*	解析：N、P都为红，违反性质4；若把P改为黑，符合性质4，显然左边少了一个黑节点，违反性质5；
*		  所以我们把G，U都改为相反色，这样一来通过G的路径的黑节点数目没变，即符合4、5，但是
*		  G变红了，若G的父节点又是红的不就有违反了4，是这样，所以经过上边操作后未结束，需把
*		  G作为起始点，即把G看做一个插入的红节点继续向上检索----属于哪种情况，按那种情况操作
*		  ~要么中间就结束，要么知道根结点（此时根结点变红，一根结点向上检索，那木有了，那就
*		  把他变为黑色吧）。
*情形4：N为红，P为红，U为黑，P为G的左孩子，N为P的左孩子（或者P为G的右孩子，N为P的左孩子；反正就是同向的）。
*	操作：如图P、G变色，P、G变换即左左单旋（或者右右单旋），结束。
*	解析：要知道经过P、G变换（旋转），变换后P的位置就是当年G的位置，所以红P变为黑，
*		  而黑G变为红都是为了不违反性质5，而维持到达叶节点所包含的黑节点的数目不变！
*情形5：N为红，P为红，U为黑，P为G的左孩子，N为P的右孩子（或者P为G的右孩子，N为P的左孩子；反正两方向相反）。
*	操作：需要进行两次变换（旋转），图中只显示了一次变换-----首先P、N变换，颜色不变；然后就变成了情形4的情况，按照情况4操作，即结束。
*	解析：由于P、N都为红，经变换，不违反性质5；然后就变成4的情形，此时G与G现在的左孩子变色，并变换，结束。
*/

template <typename K, typename V>
bool RBTree<K, V>::Insert(const K& key, const V& value = V())
{
	//根节点为空，情形1
	if (this->_root == NULL)
	{
		this->_root = new Node(key, value);
		this->_root->_col = BLACK;
		return true;
	}
	Node* parent = NULL;
	Node* cur = this->_root;
	//查找插入位置
	while (cur != NULL)
	{
		if (key < cur->_key)
		{
			parent = cur;
			cur = cur->_left;
		}
		else if (key > cur->_key)
		{
			parent = cur;
			cur = cur->_right;
		}
		else
		{
			return false;
		}
	}
	if (key < parent->_key)
	{
		cur = new Node(key, value);
		parent->_left = cur;
		cur->_parent = parent;
	}
	else
	{
		cur = new Node(key, value);
		parent->_right = cur;
		cur->_parent = parent;
	}

	//情形2：插入节点N的父节点P为黑色
	if (parent->_col == BLACK)
	{
		return true;
	}

	//情形3、4、5
	Node* grandFather = NULL;
	//走到这，说明parent->_col == RED，所以parent肯定不是根结点，所以肯定有父结点
	while ((parent != NULL) && (parent->_col == RED))
	{
		grandFather = parent->_parent;//grandFather肯定不为空,grandFather->_col == BLACK
		//parent为grandPather的左孩子
		if (parent->_key < grandFather->_key)
		{
			//情形3
			if (grandFather->_right == NULL || grandFather->_right->_col == RED)
			{
				grandFather->_col = RED;
				parent->_col = BLACK;
				if (grandFather->_right != NULL)
				{
					grandFather->_right->_col = BLACK;
				}
				cur = grandFather;
				parent = cur->_parent;
			}
			else	//uncle为黑肯定存在
			{	
				//情形5,			
				if (cur->_key > parent->_key)
				{
					this->_RolateL(parent);
					grandFather->_left = parent;
				}
				//情形4,5
				parent->_col = BLACK;
				grandFather->_col = RED;
				this->_RolateR(grandFather);
				break;
			}
		}
		//parent为grandPather的右孩子
		else
		{
			//情形3
			if ((grandFather->_left == NULL) || (grandFather->_left->_col == RED))
			{
				grandFather->_col = RED;
				parent->_col = BLACK;
				if (grandFather->_left != NULL)
				{
					grandFather->_left->_col = BLACK;
				}
				cur = grandFather;
				parent = cur->_parent;
			}
			else	//uncle为黑肯定存在
			{
				//情形5,			
				if (cur->_key < parent->_key)
				{
					this->_RolateR(parent);
					grandFather->_right = parent;
				}
				//情形4,5
				parent->_col = BLACK;//改颜色
				grandFather->_col = RED;
				this->_RolateL(grandFather);
				break;
			}
		}/*else 左右孩子*/
		
	}/*while*/
	this->_root->_col = BLACK;
	return true;
}

template <typename K, typename V>
void RBTree<K, V>::_RolateL(Node* &parent)
{
	Node* subR = parent->_right;
	Node* subRL = subR->_left;
	parent->_right = subRL;
	if (subRL)
	{
		subRL->_parent = parent;
	}
	subR->_left = parent;
	parent->_parent = subR;
	parent = subR;
}

template <typename K, typename V>
void RBTree<K, V>::_RolateR(Node* &parent)
{
	Node* subL = parent->_left;
	Node* subLR = subL->_right;
	parent->_left = subLR;
	if (subLR)
	{
		subLR->_parent = parent;
	}
	subL->_right = parent;
	parent->_parent = subL;
	parent = subL;
}
