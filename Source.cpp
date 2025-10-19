#include <iostream>
#include <random>
std::mt19937 rng(std::random_device{}());
int main()
{
    setlocale(LC_ALL, "RU-ru");
    std::wcout << L"Загадайте число и запомните его\n";
    int steps = 1, bulls = 0, num = 0, unique = 0;
WRONG_GUESS:
    if ((bulls != 0) ? (std::wcout << L"Введите позицию быка\t", std::cin >> num, bulls--, true) : (false)) goto WRONG_GUESS;
    num = std::uniform_int_distribution<int>(100, 9999)(rng), unique = int((num / 1000 != (num / 100) % 10) && (num / 1000 != (num / 10) % 10) && (num / 1000 != num % 10) && ((num / 100) % 10 != (num / 10) % 10) && ((num / 100) % 10 != num % 10) && ((num / 10) % 10 != num % 10));
    if ((unique) ? (std::wcout << steps << L") Это число " << ((num < 1000) ? (L"0") : (L"")) << num << L"? Введите количество коров и быков.\n", true) : (std::wcout, false)) std::cin >> num >> num, (num == 4 ? (std::wcout << L"Игра закончилась за " << steps << L" ходов\n") : (bulls = num, steps++, std::wcout));
    if (num == 4) return 0;
    goto WRONG_GUESS;
}