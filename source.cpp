#include <iostream>
#include <chrono>
#include "test.hpp"

int main()
{
    setlocale(LC_ALL, "RU-ru");

    test_binary_tree();

    test_binary_search_tree(); // ERROR

    return 0;
}