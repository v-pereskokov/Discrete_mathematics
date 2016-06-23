#include "Bit.h"
#include "Except.cpp"

pva::Bit::Bit() noexcept
:_bit(0) {}

pva::Bit::Bit(const pva::size_type bit)
:_bit(bit)
{
    if (!check_bit(_bit))
        _bit = 0;
}

const pva::Bit & pva::Bit::operator =(const pva::Bit &rhs)
{
    if (!check_bit(rhs._bit)) {
        _bit = 0;
        return *this;
    }
    if (this != &rhs)
        _bit = rhs._bit;
    return *this;
}

const pva::Bit & pva::Bit::operator =(const pva::size_type rhs)
{
    if (!check_bit(rhs)) {
        _bit = 0;
        return *this;
    }
    if (_bit == rhs)
        return *this;
    _bit = rhs;
    return *this;
}

pva::Bit & pva::Bit::operator &=(const pva::Bit &rhs)
{
    _bit *= rhs._bit;
    return *this;
}

pva::Bit & pva::Bit::operator |=(const pva::Bit &rhs)
{
    _bit = (_bit == 0 && rhs._bit == 0) ? 0 : 1;
    return *this;
}

pva::Bit & pva::Bit::operator +=(const pva::Bit &rhs)
{
    _bit = (_bit == rhs._bit) ? 0 : 1;
    return *this;
}

pva::Bit & pva::Bit::operator ~()
{
    pva::Bit rhs(1);
    *this += rhs;
    return *this;
}

pva::Bit::operator char ()
{
    return char();
}

pva::Bit::operator std::string()
{
    return std::to_string(_bit);
}

pva::Bit::operator pva::size_type ()
{
    return _bit;
}

bool pva::Bit::check_bit(const size_type bit)
{
    try {
        if (bit != 0 && bit != 1)
            throw pva::Except("Isn't 0 or 1");
    }
    catch (pva::Except &e) {
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

inline void pva::swap(pva::Bit &lhs, pva::Bit &rhs)
{
    Bit temp(lhs);
    lhs = rhs;
    rhs = temp;
}

inline pva::Bit pva::conjunction(const pva::Bit &lhs, const pva::Bit &rhs)
{
    pva::Bit result(lhs);
    return result &= rhs;
}

inline pva::Bit pva::disjunction(const pva::Bit &lhs, const pva::Bit &rhs)
{
    pva::Bit result(lhs);
    return result |= rhs;
}

inline pva::Bit pva::XOR(const pva::Bit &lhs, const pva::Bit &rhs)
{
    pva::Bit result(lhs);
    return result += rhs;
}

inline pva::Bit pva::negation(pva::Bit &rhs)
{
    return ~rhs;
}

inline std::string pva::BStoS(pva::Bit &bit)
{
    std::string result;
    result += std::to_string(stoi(std::to_string(static_cast<pva::size_type>(bit))));
    return result;
}