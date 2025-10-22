//#define VERBOSE_OUTPUT

#include <iostream>
#include "AVL_tree.hpp"
#include "Binary_tree.hpp"

#include <vector>
#include <chrono>
#include <random>

void test_avl_tree(const std::vector<int>& data);
std::vector<int> generate_random_array(int size);

int main()
{
	setlocale(LC_ALL, "RU-ru");

    test_avl_tree(generate_random_array(1e6));
}

std::vector<int> generate_random_array(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, size * 10);

    for (int i = 0; i < size; ++i) {
        arr[i] = dist(gen);
    }
    return arr;
}

template<typename Func>
long long measure_time(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}


void test_avl_tree(const std::vector<int>& data) {
    std::cout << "Testing AVL Tree..." << std::endl;
    AVL_tree<int> avl;

    try {
        auto insert_time = measure_time([&]() {
            for (int i = 0; i < 100000; i++) {
                avl.insert(data[i]);
            }
            });
        std::cout << "Insert time (100000 elements): " << insert_time << " ms" << std::endl;

        std::cout << "Tree height: " << avl.height() << std::endl;
        std::cout << "Tree size: " << avl.size() << std::endl;

        auto search_time = measure_time([&]() {
            for (int i = 0; i < 1000; ++i) {
                avl.contains(data[i]);
            }
            });
        std::cout << "Search time (1000 elements): " << search_time << " ms" << std::endl;

    }
    catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << std::endl;
}
