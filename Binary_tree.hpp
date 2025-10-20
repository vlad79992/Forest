#pragma once

template<typename Key>
class Binary_tree
{
private:
	Key value;
	Binary_tree* left = nullptr;
	Binary_tree* right = nullptr;
	int size = 0;

	void append_tree(Binary_tree* tree);
public:
	void insert(Key key);
	void erase(Key key);
	bool contains(Key key);
	void clear();
};

template<typename Key>
inline void Binary_tree<Key>::append_tree(Binary_tree* tree)
{
	if (tree == nullptr) return;
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
	this->size = ((this->left == nullptr) ? (0) : (this->left->size)) +
		((this->right == nullptr) ? (0) : (this->right->size)) + 1;
}

template<typename Key>
inline void Binary_tree<Key>::insert(Key key)
{
	if (this->size == 0)
	{
		this->value = key;
	}
	else
	{
		if (key < this->value)
		{
			if (this->left == nullptr) this->left = new Binary_tree;
			this->left->insert(key);
		}
		if (key > this->value)
		{
			if (this->right == nullptr) this->right = new Binary_tree;
			this->right->insert(key);
		}
	}
	this->size = ((this->left == nullptr) ? (0) : (this->left->size)) +
		((this->right == nullptr) ? (0) : (this->right->size)) + 1;
}

template<typename Key>
inline void Binary_tree<Key>::erase(Key key)
{
	if (key < this->value && this->left != nullptr)
	{
		this->left->erase(key);
		if (this->left != nullptr && this->left->size == 0)
			delete(this->left);
	}
	else if (key > this->value && this->right != nullptr)
	{
		this->right->erase(key);
		if (this->right != nullptr && this->right->size == 0)
			delete(this->right);
	}

	if (key == this->value)
	{
		if (this->left == nullptr && this->right == nullptr)
			return this->clear();

		if ((this->left == nullptr ? 0 : this->left->size) > (this->right == nullptr ? 0 : this->right->size))
		{
			Binary_tree* tmp = this->right;
			*this = *this->left;
			append_tree(tmp);
		}
		else
		{
			Binary_tree* tmp = this->left;
			*this = *this->right;
			append_tree(tmp);
		}

		this->size = ((this->left == nullptr) ? (0) : (this->left->size)) +
			((this->right == nullptr) ? (0) : (this->right->size)) + 1;
	}
}

template<typename Key>
inline bool Binary_tree<Key>::contains(Key key)
{
	if (this->size == 0) return false;
	if (key == this->value) return true;
	if (key >= this->value && this->right != nullptr) return this->right->contains(key);
	if (key < this->value && this->left != nullptr) return this->left->contains(key);
	return false;
}

template<typename Key>
inline void Binary_tree<Key>::clear()
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
	size = 0;
}