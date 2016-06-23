#pragma once

#include <iostream>

namespace pva
{
    struct Except
    {
        Except(const std::string &);
        
        std::string & what();
        
        friend std::ostream & operator <<(std::ostream &, const Except &);
        
    private:
        std::string _error; /*!< Описание ошибки*/
    };
    
    std::ostream & operator <<(std::ostream &out, const Except &except)
    {
        out << except._error;
        return out;
    }
}
