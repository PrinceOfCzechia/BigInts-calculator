#include "charray.h"
#include <string>

// CONSTRUCTORS and AUXILIARY functions

void Charray::fillWithZeros()
{
    for(unsigned i=0; i<N; i++)
    {
        this->array[i]='0';
    }
}

Charray::Charray()
{
    this->fillWithZeros();
}

Charray::Charray(unsigned long n)
{
    this->fillWithZeros();
    unsigned carry = 0;
    unsigned aux = 0;
    for(int i = 1; i<10; i++)
    {
        aux = pow(10, i);
        carry = n%aux;
        n -= carry;
        this->setNum(carry*10/aux, i-1);
    }
    this->setNum((n-(n%aux))/aux,9);
}

Charray::Charray(std::string text)
{
    this->fillWithZeros();
    unsigned length = text.length();
    for(unsigned i = 0; i<length; i++)
    {
        this->setNum(text[length-1-i]-'0',i);
    }
}

Charray::~Charray(){}

// several functions to handle instances of Charray

void Charray::setNum(unsigned n, unsigned i)
{
    if(n<10) this->array[i]=n+'0';
    else
    {
        std::ostream &out = std::cerr;
        out<<"WARNING: Invalid input was changed to zero"<<std::endl;
        this->array[i]='0';
    }
}

char Charray::getNum(unsigned i)
{
    return this->array[i];
}

std::string Charray::shortString()
{
    std::string output = "";
    bool virgin = 1;
    for(unsigned i=0; i<N; i++)
    {
        char temp = this->getNum(N-i-1);
        if(temp!='0') virgin = 0;
        if(!virgin) output+=temp;
    }
    if(virgin) output="0";
    return output;
}

std::ostream& operator<<(std::ostream& out, Charray a)
{
    bool virgin = 1;
    for(unsigned i=0; i<N; i++)
    {
        char aux = a.getNum(N-i-1);
        if(aux!='0') virgin = 0;
        if(!virgin) out<<aux;
    }
    if(virgin) out<<'0';
    out<<std::endl;
    return out;
}
