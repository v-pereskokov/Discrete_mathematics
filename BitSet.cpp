#include "BitSet.h"

pva::BitSet::BitSet() noexcept
:_size(0) {}

pva::BitSet::BitSet(const size_type size) noexcept
:_size(size)
{
    _bits.resize(_size);
    for (size_type i = 0; i < _size; ++i)
        _bits.push_back(Bit(0));
}

pva::BitSet::BitSet(const std::vector<pva::Bit> &bits) noexcept
:_size(bits.size())
{
    for (size_type i = 0; i < _size; ++i)
        _bits.push_back(bits[i]);
}

pva::BitSet::BitSet(const std::string &bits) noexcept
:_size(bits.size())
{
    for (pva::size_type i = 0; i < _size; ++i)
        _bits.push_back(static_cast<pva::Bit>(stoi(std::to_string(bits[i])) - 48));
}

pva::BitSet::BitSet(const pva::BitSet &copy) noexcept
:_size(copy.size())
{
    for (size_type i = 0; i < _size; ++i)
        _bits.push_back(copy._bits[i]);
}

void pva::BitSet::set_bits(const std::vector<Bit> &bits)
{
    _size = bits.size();
    _bits.resize(_size);
    for (size_type i = 0; i < _size; ++i)
        _bits[i] = bits[i];
}

void pva::BitSet::set_bits(const std::string &bits)
{
    _size = bits.size();
    _bits.resize(_size);
    for (pva::size_type i = 0; i < _size; ++i)
        _bits[i] = static_cast<pva::Bit>(stoi(std::to_string(bits[i])) - 48);
}

void pva::BitSet::set_bits(const pva::BitSet &bits)
{
    _size = bits.size();
    _bits.resize(_size);
    for (size_type i = 0; i < _size; ++i)
        _bits[i] = bits._bits[i];
}

pva::size_type pva::BitSet::size() const
{
    return _size;
}

void pva::BitSet::push_back(const Bit &bit)
{
    _bits.push_back(bit);
    ++_size;
}

void pva::BitSet::pop_back()
{
    _bits.pop_back();
    --_size;
}

void pva::BitSet::resize(const size_type size)
{
    if (_size == size)
        return;
    else if (_size > size)
        for (size_type i = 0; i < _size - size; ++i)
            _bits.pop_back();
    else if (_size < size)
        for (size_type i = 0; i < size - _size; ++i)
            _bits.push_back(Bit(0));
    _size = size;
    _bits.resize(_size);
}

pva::BitSet & pva::BitSet::operator =(const std::vector<pva::Bit> &bits)
{
    if (_bits != bits || _size != bits.size()) {
        _size = bits.size();
        _bits.resize(_size);
        for (size_type i = 0; i < _size; ++i)
            _bits[i] = bits[i];
    }
    return *this;
}

pva::BitSet & pva::BitSet::operator =(const pva::BitSet &rhs)
{
    if (this != &rhs || _size != rhs.size()) {
        _size = rhs._size;
        _bits.resize(_size);
        for (size_type i = 0; i < _size; ++i)
            _bits[i] = rhs._bits[i];
    }
    return *this;
}

const pva::Bit & pva::BitSet::operator [](const pva::size_type index) const
{
    if (index > _size)
        throw pva::Except("Incorrect index of BitSet");
    return _bits[index];
}

pva::Bit & pva::BitSet::operator [](const pva::size_type index)
{
    return const_cast<pva::Bit &>(static_cast<const pva::BitSet &>(*this)[index]);
}

pva::BitSet & pva::BitSet::operator &=(const pva::BitSet &rhs)
{
    if (_size == rhs.size())
        for (size_type i = 0; i < _size; ++i)
            _bits[i] &= rhs._bits[i];
    return *this;
}

pva::BitSet & pva::BitSet::operator &=(const pva::Bit &rhs)
{
    if (rhs == static_cast<pva::Bit>(0)) {
        for (pva::size_type i = 0; i < _size; ++i)
            _bits[i] = 0;
    }
    return *this;
}

pva::BitSet & pva::BitSet::operator |=(const pva::BitSet &rhs)
{
    if (_size == rhs.size())
        for (size_type i = 0; i < _size; ++i)
            _bits[i] |= rhs._bits[i];
    return *this;
}

pva::BitSet & pva::BitSet::operator |=(const pva::Bit &rhs)
{
    if (rhs == static_cast<pva::Bit>(1))
        for (pva::size_type i = 0; i < _size; ++i)
            _bits[i] = 1;
    return *this;
}

pva::BitSet & pva::BitSet::operator +=(const pva::BitSet &rhs)
{
    if (_size == rhs._size)
        for (size_type i = 0; i < _size; ++i)
            _bits[i] += rhs._bits[i];
    return *this;
}

pva::BitSet & pva::BitSet::operator +=(const pva::Bit &rhs)
{
    pva::size_type k = 0;
    for (size_type i = 0; i < _size; ++i) {
        if (_bits[i] == static_cast<pva::Bit>(1))
            ++k;
    }
    if (k == _bits.size())
        return *this;
    if (rhs == static_cast<pva::Bit>(1)) {
        if (_bits[_bits.size() - 1] == static_cast<pva::Bit>(0)) {
            _bits[_bits.size() - 1] = static_cast<pva::Bit>(1);
        }
        else {
            pva::size_type i = 0;
            while (_bits[_bits.size() - i - 1] == static_cast<pva::Bit>(1)) {
                _bits[_bits.size() - i - 1] = static_cast<pva::Bit>(0);
                ++i;
            }
            _bits[_bits.size() - i - 1] = static_cast<pva::Bit>(1);
        }
    }
    return *this;
}

pva::BitSet & pva::BitSet::operator ~()
{
    for (size_type i = 0; i < _size; ++i)
        ~_bits[i];
    return *this;
}

pva::BitSet::operator std::string ()
{
    return std::string();
}

pva::BitSet::operator pva::size_type ()
{
    return _size;
}

inline std::string pva::BStoS(pva::BitSet &bits)
{
    std::string result;
    for (pva::size_type i = 0; i < bits.size(); ++i) {
        result += std::to_string(stoi(std::to_string(static_cast<pva::size_type>(bits[i]))));
    }
    return result;
}

inline bool pva::check_n(const pva::size_type size, const pva::size_type n)
{
    if (size == pow(2, n))
        return true;
    return false;
}

inline pva::size_type pva::log_2(const pva::size_type target)
{
    return log(target) / log(2);
}