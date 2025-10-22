#define VERBOSE_OUTPUT

#include <iostream>
#include "AVL_tree.hpp"
#include "Binary_tree.hpp"

int main()
{
	setlocale(LC_ALL, "RU-ru");

	AVL_tree<int> tree;

	for (int i = 0; i < 1e6; ++i)
	{
		tree.insert(i);
	}
	std::cout << tree.size() << ' ' << tree.height() << std::endl;
	std::cout << tree.contains(7999) << std::endl;
	tree.erase(7999);
	std::cout << tree.contains(7999) << std::endl;
	std::cout << tree.size() << ' ' << tree.height() << std::endl;
}