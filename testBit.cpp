#include <iostream>
#include <vector>
#include <string>
#include "BitFunction.cpp"

int main()
{
    std::cout << "Введите вектор значений : ";
    std::string vector;
    std::cin >> vector;
    pva::BitSet bits1(vector);
    pva::BitFunction bf(bits1);
    bf.true_table();
    bf.PDNF();
    bf.PCNF();
    bf.ANF();
    return 0;
}