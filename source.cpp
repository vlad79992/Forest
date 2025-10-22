//#define VERBOSE_OUTPUT

#include <iostream>
#include "AVL_tree.hpp"
#include "Binary_tree.hpp"
#include "binary_search_tree.hpp"

#include "test.hpp"

int main()
{
	setlocale(LC_ALL, "RU-ru");

    test_avl_tree(generate_random_array(1e6));
}
