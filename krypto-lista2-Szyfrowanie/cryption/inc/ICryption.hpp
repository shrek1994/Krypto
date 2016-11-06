#pragma once

#include <sstream>

class ICryption
{
public:
    virtual std::stringstream encrypt(std::istream& in) = 0;
    virtual std::stringstream decrypt(std::istream& in) = 0;

    virtual ~ICryption() = default;
};
