#include <iostream>
#include <chrono>
#include "Binary_tree.hpp"

int main()
{
    setlocale(LC_ALL, "RU-ru");

    Binary_tree<int> tree;

    auto start_insert = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1e6; ++i) {
        if (i % 1000 == 0)
            std::cout << i << std::endl;
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

    return 0;
}