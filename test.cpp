#define VERBOSE_OUTPUT

#include <iostream>
#include "AVL_tree.hpp"

int main()
{
	setlocale(LC_ALL, "RU-ru");
	
	AVL_tree<int> tree;
	tree.insert(56);
	tree.insert(47);
	tree.insert(60);
	tree.insert(43);
	tree.insert(49);
	tree.insert(48);
	tree.insert(50);
	tree.insert(55);
	tree.insert(55);
	
	std::cout << tree << std::endl;
	std::cout << tree.size() << std::endl;
	std::cout << tree.height() << std::endl;
	
	std::cout << (tree.contains(50) ? "True" : "False") << std::endl;
	std::cout << (tree.contains(51) ? "True" : "False") << std::endl;

	tree.erase(56);
	tree.erase(56);
	
	std::cout << tree << std::endl;
	std::cout << tree.size() << std::endl;
	std::cout << tree.height() << std::endl;
	

	tree.clear();

	std::cout << tree.size() << std::endl;
	std::cout << tree.height() << std::endl;
}