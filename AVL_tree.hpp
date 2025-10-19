#pragma once
#include <iostream>

template<typename Key>
class AVL_tree
{
private:
	Key value;
	AVL_tree* left = nullptr;
	AVL_tree* right = nullptr;
	int tree_height = 0;
	int tree_size = 0;
	
	void balance(AVL_tree*);
	void right_turn();
	void left_turn();
	void big_right_turn();
	void big_left_turn();

	void append_tree(AVL_tree* tree);

	void print_json(std::ostream& os) const;
public:
	void insert(const Key key);
	bool contains(const Key key);
	void erase(const Key key);
	void clear();
	bool empty();
	int  size();
	int  height();

	friend std::ostream& operator<< (std::ostream& os, const AVL_tree<Key>& tree)
	{
		tree.print_json(os);
		return os;
	}
};



#define __max(a,b) (((a) > (b)) ? (a) : (b))
#define __min(a,b) (((a) < (b)) ? (a) : (b))

template<typename Key>
inline void AVL_tree<Key>::balance(AVL_tree* tree)
{
	if (left == nullptr && right == nullptr)
		return;
	
	if (left == nullptr)
	{
		if (right->tree_height >= 2)
			return left_turn();
	}
	
	else if (right == nullptr)
	{
		if (left->tree_height >= 2)
			return right_turn();
	}

	else if (right->tree_height - left->tree_height >= 2)
		return left_turn();

	else if (left->tree_height - right->tree_height >= 2)
		return right_turn();

	this->tree_height = __max(((this->left == nullptr) ? (0) : (this->left->tree_height)),
		((this->right == nullptr) ? (0) : (this->right->tree_height))) + 1;
	this->tree_size = ((this->left == nullptr) ? (0) : (this->left->tree_size)) +
		((this->right == nullptr) ? (0) : (this->right->tree_size)) + 1;
}

template<typename Key>
inline void AVL_tree<Key>::right_turn()
{
	AVL_tree* root = this->left;

	std::swap(*this, *root);

	root->left = this->right;
	this->right = root;

	this->right->tree_height = __max(((this->right->left == nullptr) ? (0) : (this->right->left->tree_height)),
		((this->right->right == nullptr) ? (0) : (this->right->right->tree_height))) + 1;

	this->right->tree_size = ((this->right->left == nullptr) ? (0) : (this->right->left->tree_size))
		+ ((this->right->right == nullptr) ? (0) : (this->right->right->tree_size)) + 1;
	this->tree_size = this->left->tree_size + this->right->tree_size + 1;

	this->tree_height = __max(((this->left == nullptr) ? (0) : (this->left->tree_height)),
		((this->right == nullptr) ? (0) : (this->right->tree_height))) + 1;
}

template<typename Key>
inline void AVL_tree<Key>::left_turn()
{
	AVL_tree* root = this->right;

	std::swap(*this, *root);

	root->right = this->left;
	this->left = root;

	this->left->tree_height = __max(((this->left->left == nullptr) ? (0) : (this->left->right->tree_height)),
		((this->left->left == nullptr) ? (0) : (this->left->left->tree_height))) + 1;

	this->left->tree_size = ((this->left->left == nullptr) ? (0) : (this->left->left->tree_size))
		+ ((this->left->right == nullptr) ? (0) : (this->left->right->tree_size)) + 1;
	this->tree_size = this->left->tree_size + this->right->tree_size + 1;

	this->tree_height = __max(((this->left == nullptr) ? (0) : (this->left->tree_height)),
		((this->right == nullptr) ? (0) : (this->right->tree_height))) + 1;
}

template<typename Key>
inline void AVL_tree<Key>::big_right_turn()
{
	this->left->left_turn();
	this->right_turn();
}

template<typename Key>
inline void AVL_tree<Key>::big_left_turn()
{
	this->right->right_turn();
	this->left_turn();
}

template<typename Key>
inline void AVL_tree<Key>::append_tree(AVL_tree* tree)
{
	if (tree->value < this->value)
	{
		if (this->left == nullptr)
		{
			this->left = tree;
		}
		else
		{
			this->left->append_tree(tree);
		}
	}
	else
	{
		if (this->right == nullptr)
		{
			this->right = tree;
		}
		else
		{ 
			this->right->append_tree(tree);
		}
	}
	this->tree_height = __max(((this->left == nullptr) ? (0) : (this->left->tree_height)),
		((this->right == nullptr) ? (0) : (this->right->tree_height))) + 1;
	this->tree_size = ((this->left == nullptr) ? (0) : (this->left->tree_size)) +
		((this->right == nullptr) ? (0) : (this->right->tree_size)) + 1;
	balance(this);
}

template<typename Key>
void AVL_tree<Key>::print_json(std::ostream& os) const
{
	if (this->tree_size == 0) return;
	os << "{\"value\": " << "\"" << value << "\"";
	os << ", \"height\": " << "\"" << tree_height << "\"";
	os << ", \"size\": " << "\"" << tree_size << "\"";
	os << ", \"left\":";
	(left == nullptr) ? (os << "\"null\"") : (os << *left);
	os << ", \"right\":";
	(right == nullptr) ? (os << "\"null\"") : (os << *right);
	os << "}";
	return;
}

template<typename Key>
void AVL_tree<Key>::insert(const Key key)
{
	if (this->tree_size == 0)
	{
		this->value = key;
		this->tree_height = 1;
		this->tree_size = 1;
	}
	else
	{
		if (key < this->value)
		{
			if (this->left == nullptr)
			{
				this->left = new AVL_tree<Key>;
			}
			this->left->insert(key);
			this->tree_height = __max(this->tree_height, this->left->tree_height + 1);
		}
		else if (key > this->value)
		{
			if (this->right == nullptr)
			{
				this->right = new AVL_tree<Key>;
			}
			this->right->insert(key);
			this->tree_height = __max(this->tree_height, this->right->tree_height + 1);
		}
		else
		{
#ifdef VERBOSE_OUTPUT
			std::wcerr << L"Tree already contains this value ";
			std::wcerr << key; //если значение типа нельзя вывести, то в этом месте произойдёт ошибка
			std::wcerr << std::endl;
#endif
			return;
		}
	}
	//this->tree_size++;

	balance(this);
}

template<typename Key>
bool AVL_tree<Key>::contains(const Key key)
{
	if (this->tree_size == 0) return false;
	if (key == this->value) return true;
	if (key >= this->value && this->right != nullptr) return this->right->contains(key);
	if (key <  this->value && this->left  != nullptr) return this->left->contains(key);
	return false;
}

template<typename Key>
void AVL_tree<Key>::erase(const Key key)
{
	if (key < this->value && this->left != nullptr)
		this->left->erase(key);
	else if (key > this->value && this->right != nullptr)
		this->right->erase(key);

	if (key == this->value)
	{
		if (this->left == nullptr && this->right == nullptr)
			return this->clear();

		if ((this->left == nullptr ? 0 : this->left->tree_size) > (this->right == nullptr ? 0 : this->right->tree_size))
		{
			AVL_tree* tmp = this->right;
			*this = *this->left;
			append_tree(tmp);
		}
		else
		{
			AVL_tree* tmp = this->left;
			*this = *this->right;
			append_tree(tmp);
		}
		this->tree_height = __max(((this->left == nullptr) ? (0) : (this->left->tree_height)),
			((this->right == nullptr) ? (0) : (this->right->tree_height))) + 1;
		this->tree_size = ((this->left == nullptr) ? (0) : (this->left->tree_size)) +
			((this->right == nullptr) ? (0) : (this->right->tree_size)) + 1;
	}

	balance(this);
}

template<typename Key>
void AVL_tree<Key>::clear()
{
	if (this->left != nullptr)
	{
		this->left->clear();
		delete(this->left);
	}
	if (this->right != nullptr)
	{
		this->right->clear();
		delete(this->right);
	}
	left = nullptr;
	right = nullptr;
	tree_height = 0;
	tree_size = 0;	
}

template<typename Key>
bool AVL_tree<Key>::empty()
{
	return size == 0;
}

template<typename Key>
int AVL_tree<Key>::size()
{
	return this->tree_size;
}

template<typename Key>
inline int AVL_tree<Key>::height()
{
	return tree_height;
}
