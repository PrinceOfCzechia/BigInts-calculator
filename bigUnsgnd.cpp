#include "bigUnsgnd.h"

// basic nonarithmetic functions for BigUnsgnd follow

BigUnsgnd::BigUnsgnd()
{
    this->digits = Charray();
}

BigUnsgnd::BigUnsgnd(unsigned long value)
{
    this->digits = Charray(value);
}

BigUnsgnd::BigUnsgnd(char arr[])
{
    this->digits=arr;
}

BigUnsgnd::BigUnsgnd(Charray values)
{
    this->digits = values;
}

BigUnsgnd::BigUnsgnd(std::string text)
{
    this->digits = Charray(text);
}

BigUnsgnd::~BigUnsgnd(){}

void BigUnsgnd::print()
{
    this->digits.print();
}

void BigUnsgnd::printShort()
{
    this->digits.printShort();
}

std::string BigUnsgnd::shortString()
{
    return this->digits.shortString();
}

std::ostream& operator<<(std::ostream &out, BigUnsgnd b)
{
    out<<b.getDigits();
    return out;
}

void BigUnsgnd::setNum(unsigned n, unsigned i)
{
    this->digits.setNum(n,i);
}

char BigUnsgnd::getNum(unsigned i)
{
    return this->digits.getNum(i);
}

Charray BigUnsgnd::getDigits()
{
    return this->digits;
}

// COMPARATIVE functions

bool BigUnsgnd::eq(BigUnsgnd b)
{
    for(unsigned i=0; i<N; i++)
    {
        if(this->getNum(i)!=b.getNum(i)) return false;
    }
    return true;
}

bool BigUnsgnd::greaterThan(BigUnsgnd b)
{
    unsigned i = N-1;
    while(this->getNum(i)==b.getNum(i) && i>0)
    {
        i--;
    }
    return (this->getNum(i)>b.getNum(i));
}

bool BigUnsgnd::lesserThan(BigUnsgnd b)
{
    return(!this->eq(b) && !this->greaterThan(b));
}

bool BigUnsgnd::geq(BigUnsgnd b)
{
    return (this->eq(b) | this->greaterThan(b));
}

bool BigUnsgnd::leq(BigUnsgnd b)
{
    return (this->eq(b) | this->lesserThan(b));
}

// overloaded OPERATORS of COMPARISON

bool BigUnsgnd::operator>(BigUnsgnd b)
{
    return (this->greaterThan(b));
}

bool BigUnsgnd::operator<(BigUnsgnd b)
{
    return (this->lesserThan(b));
}

bool BigUnsgnd::operator>=(BigUnsgnd b)
{
    return this->geq(b);
}

bool BigUnsgnd::operator<=(BigUnsgnd b)
{
    return this->leq(b);
}

bool BigUnsgnd::operator==(BigUnsgnd b)
{
    return this->eq(b);
}

bool BigUnsgnd::operator!=(BigUnsgnd b)
{
    return !(this->eq(b));
}

// ADDITION and corresponding overloaded OPERATOR

BigUnsgnd add(BigUnsgnd a, BigUnsgnd b)
{
    BigUnsgnd c(a);
    unsigned carry = 0;
    for(unsigned i=0; i<N; i++)
    {
        unsigned s1=(unsigned(c.getNum(i)-'0')+carry);
        unsigned s2=(unsigned(b.getNum(i)-'0'));
        carry = 0;
        unsigned s = s1+s2;
        if(s>9) carry = 1;
        s=s%10;
        c.setNum(s, i);
    }
    return c;
}

BigUnsgnd BigUnsgnd::operator+(BigUnsgnd b)
{
    return add(*this, b);
}

// SUBTRACTION (or differentiation, if you will) and overloaded OPERATOR

BigUnsgnd difference(BigUnsgnd a, BigUnsgnd b)
{
    if(a.geq(b))
    {
        BigUnsgnd result;
        short carry=0;
        bool plus=0;
        for(unsigned i=0; i<N; i++)
        {
            carry=plus;
            plus=0;
            short diff=a.getNum(i)-b.getNum(i)-carry;
            if(diff<0)
            {
                diff+=10;
                plus=1;
            }
            result.setNum(diff, i);
        }
        return result;
    }
    else return difference(b,a);
}

BigUnsgnd BigUnsgnd::operator-(BigUnsgnd b)
{
    return difference(*this, b);
}

// several AUXILIARY functions for MULTIPLICATION

BigUnsgnd BigUnsgnd::multiplyBy(unsigned q)
{
    BigUnsgnd result;
    unsigned carry = 0;
    unsigned aux = 0;
    for(unsigned i=0; i<N; i++)
    {
        unsigned c = unsigned(this->getNum(i)-'0');
        c *= q;
        result.setNum((c%10+carry)%10,i);
        if(c%10+carry>=10) aux = 1;
        carry = c/10 + aux;
        aux = 0;
    }
    return result;
}

BigUnsgnd BigUnsgnd::operator*(unsigned c)
{
    return this->multiplyBy(c);
}

BigUnsgnd BigUnsgnd::shiftLeft(unsigned int q)
{
    BigUnsgnd result;
    for(unsigned i=0; i<N-q; i++)
    {
        result.setNum(this->getNum(i)-'0', i+q);
    }
    return result;
}

// MULTIPLICATION and overloaded OPERATOR
// traditional LONG MULTIPLICATION is implemented

BigUnsgnd multiply(BigUnsgnd a, BigUnsgnd b)
{
    BigUnsgnd result;
    for(unsigned i=0; i<N; i++)
    {
        result = add(result, (a*(b.getNum(i)-'0')).shiftLeft(i));
    }
    return result;
}

BigUnsgnd BigUnsgnd::operator*(BigUnsgnd b)
{
    return multiply(*this, b);
}

// AUXILIARY function for DIVISION

BigUnsgnd BigUnsgnd::shiftRight()
{
    BigUnsgnd result;
    for(unsigned i=1; i<N; i++)
    {
        result.setNum((this->getNum(i)-'0'),i-1);
    }
    return result;
}

// DIVISION and overloaded OPERATOR
// traditinial LONG DIVISION is implemented

BigUnsgnd divide(BigUnsgnd a, BigUnsgnd b)
{
    BigUnsgnd result;
    BigUnsgnd prefix = a;
    unsigned c = 0;
    unsigned cnt = 0;
    while(prefix>=b)
    {
        while(prefix.shiftRight()>b)
        {
            prefix=prefix.shiftRight();
            cnt++;
        }
        while(prefix>=b*(c+1))
        {
            c++; // See what I did here?
        }
        result.setNum(c,cnt);
        prefix = a-(b*result);
        cnt = 0;
        c = 0;
    }
    return result;
}

BigUnsgnd BigUnsgnd::operator/(BigUnsgnd b)
{
    return divide(*this, b);
}

// MODULO and overloaded OPERATOR

BigUnsgnd modulo(BigUnsgnd a, BigUnsgnd b)
{
    return a - (a/b)*b;
}

BigUnsgnd BigUnsgnd::operator%(BigUnsgnd b)
{
    return modulo(*this,b);
}
