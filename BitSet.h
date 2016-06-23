#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Bit.cpp"

namespace pva
{
    class BitSet
    {
    public:
        BitSet() noexcept;
        
        BitSet(const size_type) noexcept;
        
        explicit BitSet(const std::vector<Bit> &) noexcept;
        
        BitSet(const std::string &) noexcept;
        
        BitSet(const BitSet &) noexcept;
        
        void set_bits(const std::vector<Bit> &);
        
        void set_bits(const std::string &);
        
        void set_bits(const BitSet &);
        
        size_type size() const;
        
        void push_back(const Bit&);
        
        void pop_back();
        
        void resize(const size_type);
        
        BitSet & operator =(const std::vector<Bit> &);
        
        BitSet & operator =(const BitSet &);
        
        const Bit & operator [](const size_type) const;
        
        Bit & operator [](const size_type);
        
        BitSet & operator &=(const BitSet &);
        
        BitSet & operator &=(const Bit &);
        
        BitSet & operator |=(const BitSet &);
        
        BitSet & operator |=(const Bit &);
        
        BitSet & operator +=(const BitSet &);
        
        BitSet & operator +=(const Bit &);
        
        BitSet & operator ~();
        
        operator std::string ();
        
        operator size_type ();
        
        friend BitSet operator &(const BitSet &, const BitSet &);
        
        friend BitSet operator |(const BitSet &, const BitSet &);
        
        friend BitSet operator +(const BitSet &, const BitSet &);
        
        friend bool operator ==(const BitSet &, const BitSet &);
        
        friend bool operator !=(const BitSet &, const BitSet &);
        
        friend bool operator >(const BitSet &, const BitSet &);
        
        friend bool operator <(const BitSet &, const BitSet &);
        
        friend bool operator >=(const BitSet &, const BitSet &);
        
        friend bool operator <=(const BitSet &, const BitSet &);
        
        friend std::ostream & operator <<(std::ostream &, const BitSet &);
        
    protected:
        size_type _size; /*!< Длина сета*/
        std::vector<Bit> _bits; /*!< Сет битов*/
    };
    
    inline std::string BStoS(BitSet &);
    
    inline bool check_n(const size_type, const size_type);
    
    inline size_type log_2(const size_type);
    
    BitSet operator &(const BitSet &lhs, const BitSet &rhs)
    {
        if (lhs.size() == rhs.size()) {
            BitSet result(lhs);
            return result &= rhs;
        }
        return BitSet(lhs.size());
    }
    
    BitSet operator |(const BitSet &lhs, const BitSet &rhs)
    {
        if (lhs.size() == rhs.size()) {
            BitSet result(lhs);
            return result |= rhs;
        }
        return BitSet(lhs.size());
    }
    
    BitSet operator +(const BitSet &lhs, const BitSet &rhs)
    {
        if (lhs.size() == rhs.size()) {
            BitSet result(lhs);
            return result += rhs;
        }
        return BitSet(lhs.size());
    }
    
    bool operator ==(const BitSet &lhs, const BitSet &rhs)
    {
        if (lhs.size() == rhs.size())
            for (size_type i = 0; i < lhs.size(); ++i)
                if (lhs._bits[i] != rhs._bits[i])
                    return false;
        return true;
    }
    
    bool operator !=(const BitSet &lhs, const BitSet &rhs)
    {
        return !(lhs == rhs);
    }
    
    bool operator >(const BitSet &lhs, const BitSet &rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        else if (lhs.size() == rhs.size())
            for (size_type i = 0; i < lhs.size(); ++i)
                if (lhs._bits[i] < rhs._bits[i])
                    return false;
        if (lhs == rhs)
            return false;
        return true;
    }
    
    bool operator <(const BitSet &lhs, const BitSet &rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        else if (lhs.size() == rhs.size())
            for (size_type i = 0; i < lhs.size(); ++i)
                if (lhs._bits[i] > rhs._bits[i])
                    return false;
        if (lhs == rhs)
            return false;
        return true;
    }
    
    bool operator >=(const BitSet &lhs, const BitSet &rhs)
    {
        return !(lhs < rhs);
    }
    
    bool operator <=(const BitSet &lhs, const BitSet &rhs)
    {
        return !(lhs > rhs);
    }
    
    std::ostream & operator <<(std::ostream &out, const BitSet &bits)
    {
        for (size_type i = 0; i < bits._size; ++i)
            out << bits._bits[i];
        return out;
    }
}