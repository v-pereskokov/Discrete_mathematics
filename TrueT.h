#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "BitSet.cpp"

namespace pva
{
    class TrueT
    {
    public:
        TrueT() noexcept;
        
        TrueT(const BitSet &) noexcept;
        
        void set_bitset(const BitSet &);
        
        void print_table();
        
    private:
        void initialization_vector(const size_type);
        
        void merger(const std::vector<BitSet> &, const pva::size_type);
        
        friend class BitFunction;
        
    protected:
        size_type _n; /*!< Число переменных вектора битов*/
        BitSet _bits; /*!< Вектор значений*/
        BitSet _vector; /*!< Вектор строки таблицы*/
        std::vector<BitSet> _table; /*!< Таблица истинности*/
        bool _flag;
    };
}