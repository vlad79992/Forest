#pragma once
#include <vector>
#include <chrono>
#include <random>

#include "AVL_tree.hpp"
#include "binary_search_tree.hpp"
#include "Binary_tree.hpp"

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

void test_binary_search_tree() {
    TreeNode* tree = new TreeNode(0);

    auto start_insert = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        if (i % 1000 == 0)
            std::cout << i << std::endl;
        insert_node(tree, i);
    }
    auto end_insert = std::chrono::high_resolution_clock::now();
    auto duration_insert = std::chrono::duration_cast<std::chrono::milliseconds>(end_insert - start_insert);
    std::cout << "Время вставки 1 млн элементов: " << duration_insert.count() << " мс\n";


    auto start_search = std::chrono::high_resolution_clock::now();
    bool found = isFound(tree, 500000);
    auto end_search = std::chrono::high_resolution_clock::now();
    auto duration_search = std::chrono::duration_cast<std::chrono::microseconds>(end_search - start_search);
    std::cout << "Поиск элемента 500000: " << (found ? "найден" : "не найден")
        << ", время: " << duration_search.count() << " мкс\n";

    auto start_clear = std::chrono::high_resolution_clock::now();
    delete_tree(tree);
    auto end_clear = std::chrono::high_resolution_clock::now();
    auto duration_clear = std::chrono::duration_cast<std::chrono::milliseconds>(end_clear - start_clear);
    std::cout << "Время очистки дерева: " << duration_clear.count() << " мс\n";

    return;
}

void test_binary_tree()
{
    Binary_tree<int> tree;

    auto start_insert = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1e6; ++i) {
        if (i % 1000 == 0)

            tree.insert(i);
    }
    auto end_insert = std::chrono::high_resolution_clock::now();
    auto duration_insert = std::chrono::duration_cast<std::chrono::milliseconds>(end_insert - start_insert);

    auto start_search = std::chrono::high_resolution_clock::now();
    bool found = tree.contains(500000);
    auto end_search = std::chrono::high_resolution_clock::now();
    auto duration_search = std::chrono::duration_cast<std::chrono::microseconds>(end_search - start_search);

    auto start_clear = std::chrono::high_resolution_clock::now();
    tree.clear();
    auto end_clear = std::chrono::high_resolution_clock::now();
    auto duration_clear = std::chrono::duration_cast<std::chrono::milliseconds>(end_clear - start_clear);

    std::cout << "Время вставки 1 млн элементов: " << duration_insert.count() << " мс\n";
    std::cout << "Поиск элемента 500000: " << (found ? "найден" : "не найден")
        << ", время: " << duration_search.count() << " мкс\n";
    std::cout << "Время очистки дерева: " << duration_clear.count() << " мс\n";
}

