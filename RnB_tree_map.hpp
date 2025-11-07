#pragma once
#include <iostream>

template <typename TKey, typename TValue>
class RnB_tree_map
{
private:
	static enum Color
	{
		BLACK = 0,
		RED = 1
	};
	class Node
	{
	public:
		TKey key;
		TValue value;
		Node* left = nullptr;
		Node* right = nullptr;
		Node* parent = nullptr;
		int height = 0;
		int size = 0;
		Color color;

		bool insert_node(Node* new_node, Node* NIL);
	};
	void right_turn(Node* node);
	void left_turn(Node* node);

	void rebalance_insert(Node* node);
	void rebalance_erase(Node* node, Node* parent, bool left);

	void clear_recursive(Node* node);

	Node* root = nullptr;
	Node* NIL;

public:
	RnB_tree_map();
	~RnB_tree_map();

	void	insert(const TKey key, const TValue value);
	void	insert(std::pair<TKey, TValue> element);
	bool	contains(const TKey key);
	TValue	at(const TKey key);
	void	erase(const TKey key);
	void	clear();
	bool	empty();
	int		size();
	int		height();

	void	print_prefix(std::ostream& os);
	void	print_infix(std::ostream& os);
	void	print_postfix(std::ostream& os);
};

#define __max(a,b) (((a) > (b)) ? (a) : (b))
#define __min(a,b) (((a) < (b)) ? (a) : (b))

template<typename TKey, typename TValue>
inline void RnB_tree_map<TKey, TValue>::right_turn(Node* node)
{
	Node* root = node->left;

	if (root == NIL) return;

	root->parent = node->parent;
	node->parent = root;

	if (root->right != NIL) root->right->parent = node;
	node->left = root->right;
	root->right = node;

	if (root->parent != NIL)
		(root->parent->left == node) ? (root->parent->left = root) : (root->parent->right = root);
	else
		this->root = root;

	node->height = __max(((node->left == NIL) ? (0) : (node->left->height)),
		((node->right == NIL) ? (0) : (node->right->height))) + 1;

	node->size = ((node->left == NIL) ? (0) : (node->left->size))
		+ ((node->right == NIL) ? (0) : (node->right->size)) + 1;

	root->size = ((root->left == NIL) ? (0) : (root->left->size))
		+ ((root->right == NIL) ? (0) : (root->right->size)) + 1;

	root->height = __max(((root->left == NIL) ? (0) : (root->left->height)),
		((root->right == NIL) ? (0) : (root->right->height))) + 1;
}

template<typename TKey, typename TValue>
inline void RnB_tree_map<TKey, TValue>::left_turn(Node* node)
{
	Node* root = node->right;

	if (root == NIL) return;

	root->parent = node->parent;
	node->parent = root;

	if (root->left != NIL) root->left->parent = node;
	node->right = root->left;
	root->left = node;

	if (root->parent != NIL)
		(root->parent->left == node) ? (root->parent->left = root) : (root->parent->right = root);
	else
		this->root = root;

	node->height = __max(((node->left == NIL) ? (0) : (node->left->height)),
		((node->right == NIL) ? (0) : (node->right->height))) + 1;

	node->size = ((node->left == NIL) ? (0) : (node->left->size))
		+ ((node->right == NIL) ? (0) : (node->right->size)) + 1;

	root->size = ((root->left == NIL) ? (0) : (root->left->size))
		+ ((root->right == NIL) ? (0) : (root->right->size)) + 1;

	root->height = __max(((root->left == NIL) ? (0) : (root->left->height)),
		((root->right == NIL) ? (0) : (root->right->height))) + 1;
}

template<typename TKey, typename TValue>
inline void RnB_tree_map<TKey, TValue>::rebalance_insert(Node* node)
{
	if (node->parent == NIL || node->parent->parent == NIL) return;
	if (node->parent->color != RED) return;

	if (node->parent->parent->left == node->parent)
	{
		if (node->parent->parent->right->color == RED)
		{
			node->parent->color = BLACK;
			node->parent->parent->color = RED;
			node->parent->parent->right->color = BLACK;
			rebalance_insert(node->parent->parent);
		}
		else
		{
			if (node->parent->right == node)
			{
				left_turn(node->parent);
				node = node->left;
			}
			right_turn(node->parent->parent);
			node->parent->color = BLACK;
			node->parent->right->color = RED;
		}
	}
	else
	{
		if (node->parent->parent->left->color == RED)
		{
			node->parent->color = BLACK;
			node->parent->parent->color = RED;
			node->parent->parent->left->color = BLACK;
			rebalance_insert(node->parent->parent);
		}
		else
		{
			if (node->parent->left == node)
			{
				right_turn(node->parent);
				node = node->right;
			}
			left_turn(node->parent->parent);
			node->parent->color = BLACK;
			node->parent->left->color = RED;
		}
	}
}

template<typename TKey, typename TValue>
inline void RnB_tree_map<TKey, TValue>::rebalance_erase(Node* node, Node* parent, bool left)
{
	while (node != root && (node == NIL || node->color == BLACK)) {
		if (left) {
			Node* bro = parent->right;
			if (bro->color == RED)
			{
				bro->color = BLACK;
				parent->color = RED;
				left_turn(parent);
				bro = parent->right;
			}
			else if (bro->left->color == BLACK && bro->right->color == BLACK)
			{
				if (bro != NIL)
					bro->color = RED;
				node = parent;
				if (node == root) break;
				parent = node->parent;
				left = (node == parent->left);
			}
			else if (bro->right->color == BLACK)
			{
				bro->left->color = BLACK;
				bro->color = RED;
				right_turn(bro);
				bro = parent->right;
			}
			else
			{
				bro->color = parent->color;
				parent->color = BLACK;
				bro->right->color = BLACK;
				left_turn(parent);
				node = root;
			}
		}
		else {
			Node* bro = parent->left;
			if (bro->color == RED)
			{
				bro->color = BLACK;
				parent->color = RED;
				right_turn(parent);
				bro = parent->left;
			}
			else if (bro->left->color == BLACK && bro->right->color == BLACK)
			{
				if (bro != NIL)
					bro->color = RED;
				node = parent;
				if (node == root) break;
				parent = node->parent;
				left = (node == parent->left);
			}
			else if (bro->left->color == BLACK)
			{
				bro->right->color = BLACK;
				bro->color = RED;
				left_turn(bro);
				bro = parent->left;
			}
			else
			{
				bro->color = parent->color;
				parent->color = BLACK;
				bro->left->color = BLACK;
				right_turn(parent);
				node = root;
			}
		}
	}
	node->color = BLACK;
}

template<typename TKey, typename TValue>
inline void RnB_tree_map<TKey, TValue>::clear_recursive(Node* node)
{
	if (node == NIL) return;
	clear_recursive(node->left);
	clear_recursive(node->right);
	delete node;
}

template<typename TKey, typename TValue>
inline void RnB_tree_map<TKey, TValue>::insert(const TKey key, const TValue value)
{
	if (this->root == NIL)
	{
		this->root = new Node;
		this->root->key = key;
		this->root->color = BLACK;
		this->root->left = this->root->right = this->root->parent = NIL;
		return;
	}
	Node* new_node = new Node;
	new_node->key = key;
	new_node->color = RED;
	new_node->left = new_node->right = new_node->parent = NIL;
	new_node->value = value;
	if (this->root->insert_node(new_node, NIL))
	{
		rebalance_insert(new_node);
		this->root->color = BLACK;
	}
}

template<typename TKey, typename TValue>
inline void RnB_tree_map<TKey, TValue>::insert(std::pair<TKey, TValue> element)
{
	this->insert(element.first, element.second);
}

template<typename TKey, typename TValue>
inline bool RnB_tree_map<TKey, TValue>::contains(const TKey key)
{
	if (this->root == NIL) return false;

	Node* cur_node = this->root;

	while (true)
	{
		if (key == cur_node->key)
			return true;
		if (key > cur_node->key)
		{
			if (cur_node->right == NIL)
				return false;
			cur_node = cur_node->right;
		}
		else
		{
			if (cur_node->left == NIL)
				return false;
			cur_node = cur_node->left;
		}
	}
}

template<typename TKey, typename TValue>
inline TValue RnB_tree_map<TKey, TValue>::at(const TKey key)
{
	if (this->root == NIL) 
		throw std::out_of_range("Key not found in RnB_tree_map");

	Node* cur_node = this->root;

	while (cur_node != NIL)
	{
		if (key == cur_node->key)
			return cur_node->value;
		if (key > cur_node->key)
			cur_node = cur_node->right;
		else
			cur_node = cur_node->left;
	}
	throw std::out_of_range("Key not found in RnB_tree_map");
}

template<typename TKey, typename TValue>
inline void RnB_tree_map<TKey, TValue>::erase(const TKey key)
{
	if (this->root == NIL) return;

	Node* cur_node = this->root;

	while (cur_node != NIL)
	{
		if (key == cur_node->key)
		{
			if (cur_node->left == NIL && cur_node->right == NIL)
			{
				if (cur_node->parent != NIL)
					(cur_node->parent->left == cur_node) ? (cur_node->parent->left = NIL) : (cur_node->parent->right = NIL);
				else
					this->root = NIL;
				if (cur_node->color == BLACK && cur_node->parent != NIL)
				{
					bool left = (cur_node->parent->left == cur_node);
					rebalance_erase(NIL, cur_node->parent, left);
				}
				delete(cur_node);
				return;
			}
			else if (cur_node->left == NIL || cur_node->right == NIL)
			{
				Node* replacement = (cur_node->left != NIL) ? cur_node->left : cur_node->right;
				if (cur_node->parent != NIL)
				{
					if (cur_node->parent->left == cur_node)
					{
						cur_node->parent->left = replacement;
						replacement->parent = cur_node->parent;
					}
					else
					{
						cur_node->parent->right = replacement;
						replacement->parent = cur_node->parent;
					}
				}
				else
				{
					this->root = replacement;
					replacement->parent = NIL;
				}
				if (cur_node->color == BLACK)
				{
					bool left = (replacement == replacement->parent->left);
					rebalance_erase(replacement, replacement->parent, left);
				}
				delete(cur_node);
				return;
			}
			else if (cur_node->left != NIL && cur_node->right != NIL)
			{
				Node* successor = cur_node->right;
				while (successor->left != NIL) successor = successor->left;

				cur_node->key = successor->key;
				Node* parent = successor->parent;
				bool left = (parent->left == successor);
				Node* x = successor->right;
				if (left)
				{
					parent->left = x;
					if (x != NIL)
						x->parent = parent;
				}
				else
				{
					parent->right = x;
					if (x != NIL)
						x->parent = parent;
				}

				if (successor->color == BLACK)
				{
					rebalance_erase(x, parent, left);
				}
				delete(successor);
				return;
			}
		}
		if (key > cur_node->key)
		{
			cur_node = cur_node->right;
		}
		else
		{
			cur_node = cur_node->left;
		}
	}
}

template<typename TKey, typename TValue>
inline void RnB_tree_map<TKey, TValue>::clear()
{
	clear_recursive(root);
	root = NIL;
}

template<typename TKey, typename TValue>
inline bool RnB_tree_map<TKey, TValue>::empty()
{
	return this->root == NIL;
}

template<typename TKey, typename TValue>
inline int RnB_tree_map<TKey, TValue>::size()
{
	if (this->root == NIL) return 0;
	return this->root->size;
}

template<typename TKey, typename TValue>
inline int RnB_tree_map<TKey, TValue>::height()
{
	if (this->root == NIL) return 0;
	return this->root->height;
}

template<typename TKey, typename TValue>
inline RnB_tree_map<TKey, TValue>::RnB_tree_map()
{
	NIL = new Node;
	NIL->color = BLACK;
	NIL->left = NIL->right = NIL->parent = NIL;
	NIL->height = 0;
	NIL->size = 0;
	root = NIL;
}

template<typename TKey, typename TValue>
inline RnB_tree_map<TKey, TValue>::~RnB_tree_map()
{
	this->clear();
	delete(NIL);
}

template<typename TKey, typename TValue>
inline bool RnB_tree_map<TKey, TValue>::Node::insert_node(Node* new_node, Node* NIL)
{
	if (new_node->key < this->key)
	{
		if (this->left == NIL)
		{
			new_node->parent = this;
			this->left = new_node;
		}
		else
		{
			if (!this->left->insert_node(new_node, NIL))
				return false;
		}
	}
	else if (new_node->key > this->key)
	{
		if (this->right == NIL)
		{
			new_node->parent = this;
			this->right = new_node;
		}
		else
		{
			if (!this->right->insert_node(new_node, NIL))
				return false;
		}
	}
	else
	{
		delete(new_node);
#ifdef VERBOSE_OUTPUT
		std::wcerr << L"Tree already contains this value ";
		std::wcerr << new_node->value; //если значение типа нельзя вывести, то в этом месте произойдёт ошибка
		std::wcerr << std::endl;
#endif
		return false;
	}
	this->size = ((this->left != NIL) ? (this->left->size) : (0)) +
		((this->right != NIL) ? (this->right->size) : (0)) + 1;

	this->height = __max(((this->left != NIL) ? (this->left->height) : (0)),
		((this->right != NIL) ? (this->right->height) : (0))) + 1;

	return true;
}