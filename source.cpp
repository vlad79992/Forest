#include <iostream>
#include <chrono>
#include "RnB_tree_set.hpp"
#include "RnB_tree_map.hpp"

int main()
{
	RnB_tree_set<int> penis;
	for (int i = 0; i < 1e6; ++i)
	{
		penis.insert(i);
	}
}