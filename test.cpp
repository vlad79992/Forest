#define VERBOSE_OUTPUT

#include <iostream>
#include "binary_search_tree.h"

int main()
{
	setlocale(LC_ALL, "RU-ru");
	BinarySearchTree tree;
	auto* root = new BinarySearchTree::TreeNode(0);
	for (int i = 0; i < 500000; i++) {
		tree.insert_node(root, i);
	}
	vector<int> tree_elements = tree.get_tree_data(root);
	for (int num: tree_elements) {
		std::cout << num << " ";
	}
	std::cout << std::endl;
}