#include "TrueT.h"

pva::TrueT::TrueT() noexcept
:_n(0) {}

pva::TrueT::TrueT(const pva::BitSet &bits) noexcept
:_n(log_2(bits.size())), _flag(true)
{
    if (check_n(bits.size(), _n)) {
        _bits.resize(bits.size());
        for (size_type i = 0; i < _bits.size(); ++i)
            _bits[i] = bits[i];
        initialization_vector(_n);
    } else
        _flag = false;
}

void pva::TrueT::set_bitset(const BitSet &bits)
{
    _n = (log_2(bits.size()));
    _flag = check_n(bits.size(), _n);
    if (_flag) {
        _bits.resize(bits.size());
        for (size_type i = 0; i < _bits.size(); ++i)
            _bits[i] = bits[i];
        initialization_vector(_n);
    }
}

void pva::TrueT::print_table()
{
    if (_flag) {
        merger(_table, _n);
        for (pva::size_type i = 1; i <= _n; ++i)
            std::cout << "x" << i << "| ";
        std::cout << "f" << std::endl;
        for (pva::size_type i = 0; i < pow(2, _n); ++i) {
            for (pva::size_type j = 0; j < _n; ++j) {
                std::cout << _table[i][j] << " | ";
            }
            std::cout << _table[i][_n] << std::endl;
        }
    } else
        std::cout << "Impossible print table" << std::endl;
}

void pva::TrueT::initialization_vector(const pva::size_type n)
{
    for (pva::size_type i = 0; i < n; ++i)
        _vector.push_back(static_cast<pva::Bit>(0));
}

void pva::TrueT::merger(const std::vector<pva::BitSet> &table, const pva::size_type n)
{
    pva::BitSet _pretable(n + 1);
    for (pva::size_type i = 0; i < pow(2, n); ++i) {
        std::string temp = BStoS(_vector) + BStoS(_bits[i]);
        _pretable.set_bits(temp);
        _table.push_back(_pretable);
        _vector += static_cast<pva::Bit>(1);
    }
}