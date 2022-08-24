#ifndef BIGINTEXCPT_H
#define BIGINTEXCPT_H

#include <exception>
#include <string>

class BigIntException : public std::exception
{
    std::string message;
public:
    BigIntException(std::string msg): message(msg){}
    virtual const char* what() const noexcept
    {
        return message.c_str();
    }
};

#endif // BIGINTEXCPT_H
