#pragma once
#include <iostream>

template <typename Key>
class RnB_tree
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
		Key value;
		Node* left = nullptr;
		Node* right = nullptr;
		Node* parent = nullptr;
		int height = 1;
		int size = 1;
		Color color;

		void insert_node(Node* new_node);

		void right_turn();
		void left_turn();
	};

	Node* node = nullptr;
public:
	void insert(const Key key);
	bool contains(const Key key);
	void erase(const Key key);
	void clear();
	bool empty();
	int  size();
	int  height();

	void print_prefix(std::ostream& os);
	void print_infix(std::ostream& os);
	void print_postfix(std::ostream& os);
};

#define __max(a,b) (((a) > (b)) ? (a) : (b))
#define __min(a,b) (((a) < (b)) ? (a) : (b))

template<typename Key>
inline void RnB_tree<Key>::insert(const Key key)
{
	if (this->node == nullptr) // пустое дерево, добавл€ем корень
	{
		this->node = new Node;
		this->node->value = key;
		this->node->color = BLACK;
		return;
	}
	Node* new_node = new Node;
	new_node->value = key;
	new_node->color = RED;
	this->node->insert_node(new_node);
}

template<typename Key>
inline bool RnB_tree<Key>::contains(const Key key)
{
	if (this->node == nullptr) return false;

	Node* cur_node = this->node;

	while (true)
	{
		if (key == cur_node->value)
			return true;
		if (key > cur_node->value)
		{
			if (cur_node->right == nullptr)
				return false;
			cur_node = cur_node->right;
		}
		else
		{
			if (cur_node->left == nullptr)
				return false;
			cur_node = cur_node->left;
		}
	}
}

template<typename Key>
inline bool RnB_tree<Key>::empty()
{
	return this->node == nullptr;
}

template<typename Key>
inline int RnB_tree<Key>::size()
{
	if (this->node == nullptr) return 0;
	return this->node->size;
}

template<typename Key>
inline int RnB_tree<Key>::height()
{
	if (this->node == nullptr) return 0;
	return this->node->height;
}

template<typename Key>
inline void RnB_tree<Key>::Node::insert_node(Node* new_node)
{
	if (new_node->value < this->value)
	{
		if (this->left == nullptr)
		{
			new_node->parent = this;
			this->left = new_node;
		}
		else
		{
			this->left->insert_node(new_node);
		}
	}
	else if (new_node->value > this->value)
	{
		if (this->right == nullptr)
		{
			new_node->parent = this;
			this->right = new_node;
		}
		else
		{
			this->right->insert_node(new_node);
		}
	}
	else
	{
		delete(new_node);
#ifdef VERBOSE_OUTPUT
		std::wcerr << L"Tree already contains this value ";
		std::wcerr << key; //если значение типа нельз€ вывести, то в этом месте произойдЄт ошибка
		std::wcerr << std::endl;
#endif
		return;
	}
	this->size = ((this->left != nullptr) ? (this->left->size) : (0)) +
		((this->right != nullptr) ? (this->right->size) : (0)) + 1;

	this->height = __max(((this->left != nullptr) ? (this->left->height) : (0)),
		((this->right != nullptr) ? (this->right->height) : (0))) + 1;
}

template<typename Key>
inline void RnB_tree<Key>::Node::right_turn()
{

}

template<typename Key>
inline void RnB_tree<Key>::Node::left_turn()
{
}
