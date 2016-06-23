#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include "TrueT.cpp"

namespace pva
{
    std::string sdisjunction("\\/");
    std::string sconjunction("/\\");
    
    class BitFunction
    {
    public:
        BitFunction() noexcept;
        
        BitFunction(const BitFunction &);
        
        BitFunction(const BitSet &);
        
        BitFunction & operator =(const BitFunction &);
        
        BitFunction & operator =(const BitSet &);
        
        size_type n() const;
        
        const Bit & operator [](const size_type) const;
        
        Bit & operator [](const size_type);
        
        /*
         * Вывод таблицы истинности
         */
        void true_table();
        
        /*
         * Совершенная дизъюнктивная нормальная форма
         */
        void PDNF();
        
        /*
         * Совершенная конъюктивная нормальная форма
         */
        void PCNF();
        
        /*
         * Алгебраическая нормальная форма
         */
        void ANF();
        
        friend std::ostream & operator <<(std::ostream &, const BitFunction &);
        
    private:
        BitSet triangle(const pva::BitSet &, pva::BitSet &, pva::BitSet &, size_type);
        
    private:
        BitSet _bits; /*!< Сет битов*/
        std::string _target; /*!< Строка из битов*/
        size_type _size; /*!< Длина вектора битов*/
        size_type _n; /*!< Число переменных вектора битов*/
        TrueT _table; /*!< Таблица истинности*/
        bool _flag; /*!< Флаг на проведение операций с вектором битов*/
    };
    
    /*
     * Функция вывода таблицы истинности булевой функции, СДНФ, СКНФ и АНФ
     */
    inline void complex(BitFunction &);
    
    std::ostream & operator <<(std::ostream &out, const BitFunction &bitfunction)
    {
        for (size_type i = 0; i < bitfunction._size; ++i)
            out << bitfunction._bits[i];
        return out;
    }
}
