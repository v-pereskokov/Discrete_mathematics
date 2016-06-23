#pragma once

#include <iostream>
#include <string>

namespace pva
{
    using size_type = std::size_t;
    
    class Bit
    {
    public:
        Bit() noexcept;
        
        explicit Bit(const size_type);
        
        const Bit & operator =(const Bit &);
        
        const Bit & operator =(const pva::size_type);
        
        Bit & operator &=(const Bit &);
        
        Bit & operator |=(const Bit &);
        
        Bit & operator +=(const Bit &);
        
        Bit & operator ~();
        
        operator char ();
        
        operator std::string ();
        
        operator size_type ();
        
        friend Bit operator &(const Bit &, const Bit &);
        
        friend Bit operator |(const Bit &, const Bit &);
        
        friend Bit operator +(const Bit &, const Bit &);
        
        friend bool operator ==(const Bit &, const Bit &);
        
        friend bool operator !=(const Bit &, const Bit &);
        
        friend bool operator >(const Bit &, const Bit &);
        
        friend bool operator <(const Bit &, const Bit &);
        
        friend bool operator >=(const Bit &, const Bit &);
        
        friend bool operator <=(const Bit &, const Bit &);
        
        friend std::ostream & operator <<(std::ostream &, const Bit &);
        
    private:
        bool check_bit(const size_type);
        
    protected:
        size_type _bit; /*!< Бит*/
    };
    
    inline void swap(Bit &, Bit &);
    
    inline Bit conjunction(const Bit &, const Bit &);
    
    inline Bit disjunction(const Bit &, const Bit &);
    
    inline Bit XOR(const Bit &, const Bit &);
    
    inline Bit negation(Bit &r);
    
    inline std::string BStoS(Bit &);
    
    Bit operator &(const Bit &lhs, const Bit &rhs)
    {
        Bit result(lhs);
        return result &= rhs;
    }
    
    Bit operator |(const Bit &lhs, const Bit &rhs)
    {
        Bit result(lhs);
        return result |= rhs;
    }
    
    Bit operator +(const Bit &lhs, const Bit &rhs)
    {
        Bit result(lhs);
        return result += rhs;
    }
    
    bool operator ==(const Bit &lhs, const Bit &rhs)
    {
        return lhs._bit == rhs._bit;
    }
    
    bool operator !=(const Bit &lhs, const Bit &rhs)
    {
        return !(lhs == rhs);
    }
    
    inline bool operator >(const Bit &lhs, const Bit &rhs)
    {
        return lhs._bit > rhs._bit;
    }
    
    inline bool operator <(const Bit &lhs, const Bit &rhs)
    {
        return lhs._bit < rhs._bit;
    }
    
    inline bool operator >=(const pva::Bit &lhs, const pva::Bit &rhs)
    {
        return !(lhs < rhs);
    }
    
    inline bool operator <=(const pva::Bit &lhs, const pva::Bit &rhs)
    {
        return !(lhs > rhs);
    }
    
    std::ostream & operator <<(std::ostream &out, const Bit &bit)
    {
        out << bit._bit;
        return out;
    }
}