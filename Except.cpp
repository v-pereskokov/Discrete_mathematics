#include "Except.h"

pva::Except::Except(const std::string& error)
:_error(error) {}

std::string & pva::Except::what()
{
    return _error;
}