#include "BitFunction.h"

pva::BitFunction::BitFunction() noexcept
:_size(0), _n(0), _flag(false) {}

pva::BitFunction::BitFunction(const pva::BitFunction &copy)
:_size(copy._size), _n(copy._n), _flag(copy._flag)
{
    if (_flag) {
        _bits.resize(_size);
        for (size_type i = 0; i < _size; ++i)
            _bits[i] = copy._bits[i];
    }
    _table.set_bitset(_bits);
}

pva::BitFunction::BitFunction(const pva::BitSet &copy)
:_size(copy.size()), _n(log_2(_size))
{
    if (check_n(_size, _n) || !(_size & 1)) {
        _bits.resize(_size);
        for (size_type i = 0; i < _size; ++i)
            _bits[i] = copy[i];
        _flag = true;
    }
    else
        _flag = false;
    _table.set_bitset(_bits);
}

pva::BitFunction & pva::BitFunction::operator =(const pva::BitFunction &copy)
{
    if ((_size != copy._size || _bits != copy._bits) && !(copy._n & 1)) {
        _size = copy._size;
        _n = copy._n;
        _flag = copy._flag;
        for (pva::size_type i = 0; i < _size; ++i)
            _bits[i] = copy._bits[i];
    }
    _table.set_bitset(_bits);
    return *this;
}

pva::BitFunction & pva::BitFunction::operator =(const pva::BitSet &copy)
{
    if ((_size != copy.size() || _bits != copy) && !(copy.size() & 1)) {
        _size = copy.size();
        _n = log_2(_size);
        _flag = check_n(_size, _n);
        if (_flag)
            for (pva::size_type i = 0; i < _size; ++i)
                _bits[i] = copy[i];
    }
    _table.set_bitset(_bits);
    return *this;
}

pva::size_type pva::BitFunction::n() const
{
    return _n;
}

const pva::Bit & pva::BitFunction::operator [](const pva::size_type index) const
{
    if (index > _size)
        throw pva::Except("Incorrect index of BitSet");
    return _bits[index];
}

pva::Bit & pva::BitFunction::operator [](const pva::size_type index)
{
    return const_cast<pva::Bit &>(static_cast<const pva::BitFunction &>(*this)[index]);
}

inline void pva::BitFunction::true_table()
{
    if (_flag)
        _table.print_table();
}

void pva::BitFunction::PDNF()
{
    if (_flag) {
        std::string result;
        for (pva::size_type i = 0; i < pow(2, _table._n); ++i) {
            if (_table._bits[i] == static_cast<pva::Bit>(1)) {
                for (pva::size_type j = 0; j < _n; ++j) {
                    if (j == 0)
                        result += "(";
                    if (_table._table[i][j] == static_cast<pva::Bit>(1)) {
                        result += "x" + std::to_string(j + 1);
                    } else
                        result += "-x" + std::to_string(j + 1);
                    if (j == _n - 1)
                        result += ")";
                    else
                        result += sconjunction;
                }
                for (pva::size_type k = i + 1; k < pow(2, _table._n); ++k) {
                    if (_table._bits[k] == static_cast<pva::Bit>(1)) {
                        result += sdisjunction;
                        break;
                    }
                }
            }
        }
        std::cout << "PDNF: " << result << std::endl;
    } else
        std::cout << "Impossible!" << std::endl;
}

void pva::BitFunction::PCNF()
{
    if (_flag) {
        std::string result;
        for (pva::size_type i = 0; i < pow(2, _table._n); ++i) {
            if (_table._bits[i] == static_cast<pva::Bit>(0)) {
                for (pva::size_type j = 0; j < _n; ++j) {
                    if (j == 0)
                        result += "(";
                    if (_table._table[i][j] == static_cast<pva::Bit>(0)) {
                        result += "x" + std::to_string(j + 1);
                    } else
                        result += "-x" + std::to_string(j + 1);
                    if (j == _n - 1)
                        result += ")";
                    else
                        result += sdisjunction;
                }
                for (pva::size_type k = i + 1; k < pow(2, _table._n); ++k) {
                    if (_table._bits[k] == static_cast<pva::Bit>(0)) {
                        result += sconjunction;
                        break;
                    }
                }
            }
        }
        std::cout << "PCNF: " << result << std::endl;
    }
}

void pva::BitFunction::ANF()
{
    if (_flag) {
        std::string result;
        pva::BitSet bits_less = _bits;
        pva::BitSet final;
        pva::BitFunction::triangle(bits_less, final, pow(2, _n));

        std::vector<std::string> out;
        initialization_vector_x(out, _n);
        for (auto &v : out)
            std::cout << v << std::endl;
        for (pva::size_type i = 0; i < final.size(); ++i) {
            if (final[i] == static_cast<pva::Bit>(1)) {
                result += out[i];
                for (pva::size_type k = i + 1; k < pow(2, _table._n); ++k) {
                    if (final[k] == static_cast<pva::Bit>(1)) {
                        result += "+";
                        break;
                    }
                }
            }
        }
        std::cout << "ANF: " << result << std::endl;
    }
}

pva::BitSet pva::BitFunction::triangle(pva::BitSet &bits_less, pva::BitSet &bits_final, pva::size_type n)
{
    if (n != 0) {
        bits_less.resize(n);
        bits_final.push_back(bits_less[0]);
        for (pva::size_type j = 0; j < n; ++j)
            bits_less[j] += bits_less[j + 1];
        pva::BitFunction::triangle(bits_less, bits_final, n - 1);
    }
    return bits_final;
}

std::vector<std::string> pva::BitFunction::initialization_vector_x(std::vector<std::string> & vector, const pva::size_type n)
{
    for (pva::size_type i = 0; i < pow(2, n); ++i) {
        if (i == 0)
            vector.push_back("1");
        else {
            std::string in;
            for (pva::size_type j = 0; j < n; ++j) {
                if (_table._table[i][j] == static_cast<pva::Bit>(1))
                    in += "x" + std::to_string(j + 1);
            }
            vector.push_back(in);
        }
    }
    return vector;
}

void pva::complex(BitFunction &bitfunction)
{
    bitfunction.true_table();
    bitfunction.PDNF();
    bitfunction.PCNF();
    bitfunction.ANF();
}
