#include "bigInt.h"
#include "bigIntExcpt.h"

// basic nonarithmetic functions for BigInt

BigInt::BigInt()
{
    abs = BigUnsgnd();
    sgn = 1;
}

BigInt::BigInt(long val)
{
    abs = BigUnsgnd(val);
    sgn = (val>=0 ? 1 : 0);
}

BigInt::BigInt(std::string text)
{
    if(text[0]=='-' | text[0]=='u')
    {
        this->setSgn(0);
        this->setAbs(BigUnsgnd(text.erase(0,1)));
    }
    else
    {
        this->setSgn(1);
        this->setAbs(BigUnsgnd(text));
    }
}

BigInt::BigInt(BigUnsgnd val, bool sign)
{
    abs = val;
    sgn = sign;
}

BigInt::~BigInt(){}

std::string BigInt::shortString() // new function
{
    std::string output = "";
    if(*this<BigInt()) output.append("-");
    output.append(this->getAbs().shortString());
    return output;
}

std::ostream &operator<<(std::ostream &out, BigInt b)
{
    b.getSgn()==1 ? out<<'+' : out<<'-';
    out<<b.getAbs();
    return out;
}

BigUnsgnd BigInt::getAbs()
{
    return this->abs;
}

void BigInt::setAbs(BigUnsgnd value)
{
    this->abs=value;
}

bool BigInt::getSgn()
{
    return this->sgn;
}

void BigInt::setSgn(bool sign)
{
    this->sgn=sign;
}

// COMPARATIVE functions and overloaded OPERATORS
// lots of them, beware

bool BigInt::eq(BigInt b)
{
    if(this->sgn!=b.sgn) return false;
    for(unsigned i=0; i<N; i++)
    {
        if(this->abs.getNum(i)!=b.abs.getNum(i)) return false;
    }
    return true;
}

bool BigInt::greaterThan(BigInt b)
{
    if(this->sgn!=b.sgn) return (this->sgn>b.sgn ? true : false);
    else if (this->sgn && b.sgn) return this->abs.greaterThan(b.abs);
    else return this->abs.lesserThan(b.abs);
}

bool BigInt::lesserThan(BigInt b)
{
    if(this->sgn!=b.sgn) return (this->sgn<b.sgn ? true : false);
    else if (this->sgn && b.sgn) return this->abs.lesserThan(b.abs);
    else return this->abs.greaterThan(b.abs);
}

bool BigInt::geq(BigInt b)
{
    return (this->eq(b) | this->greaterThan(b));
}

bool BigInt::leq(BigInt b)
{
    return (this->eq(b) | this->lesserThan(b));
}

bool BigInt::operator==(BigInt b)
{
    return this->eq(b);
}

bool BigInt::operator!=(BigInt b)
{
    return !(this->eq(b));
}

bool BigInt::operator>(BigInt b)
{
    return this->greaterThan(b);
}

bool BigInt::operator<(BigInt b)
{
    return this->lesserThan(b);
}

bool BigInt::operator>=(BigInt b)
{
    return this->geq(b);
}

bool BigInt::operator<=(BigInt b)
{
    return this->leq(b);
}

// ARITHMETICS

// ADDITION, SUBTRACTION and overloaded OPERATORS

BigInt add(BigInt a, BigInt b)
{
    BigInt result = BigInt();
    if(a.getSgn()==b.getSgn())
    {
        result.setAbs(a.getAbs()+b.getAbs());
        result.setSgn(a.getSgn());
    }
    else
    {
        result.setAbs(a.getAbs()-b.getAbs());
        if(a.getSgn()) result.setSgn(a.getAbs()>=b.getAbs() ? 1 : 0);
        else result.setSgn(a.getAbs()>=b.getAbs() ? 0 : 1);
    }
    return result;
}

BigInt subtract(BigInt a, BigInt b)
{
    b.setSgn(!(b.getSgn()));
    return add(a, b);
}

BigInt BigInt::operator+(BigInt b)
{
    return add(*this, b);
}

BigInt BigInt::operator-(BigInt b)
{
    return subtract(*this, b);
}

// MULTIPLICATION and overloaded OPERATOR

BigInt multiply(BigInt a, BigInt b)
{
    BigInt result = BigInt();
    result.setAbs(a.getAbs()*b.getAbs());
    result.setSgn(a.getSgn()==b.getSgn());
    return result;
}

BigInt BigInt::operator*(BigInt b)
{
    return multiply(*this, b);
}

// DIVISION and overloaded OPERATOR

BigInt divide(BigInt a, BigInt b)
{
    if(b==BigInt())
    {
        throw BigIntException("WARNING: Attemped division by zero");
    }
    BigInt result = BigInt();
    result.setAbs(a.getAbs()/b.getAbs());
    result.setSgn(a.getSgn()==b.getSgn());
    return result;
}

BigInt BigInt::operator/(BigInt b)
{
    return divide(*this,b);
}

// MODULO and overloaded OPERATOR
// the definition of sgn works such, that (a/b)*b + a%b = a

/*
BigInt modulo(BigInt a, BigInt b)
{
    if(b==BigInt()) throw BigIntException("WARNING: Attempting to calculate remainder of division by zero");
    BigInt result = BigInt();
    result.setAbs(a.getAbs()%b.getAbs());
    result.setSgn(a.getSgn());
    return result;
}
BigInt BigInt::operator%(BigInt b)
{
    return modulo(*this,b);
}
*/

// POWER functionality and overloaded OPERATOR

BigInt power(BigInt b, unsigned q)
{
    if(q==0) return BigInt(1);
    BigInt result = b;
    for(unsigned i=1; i<q; i++)
    {
        result=result*b;
    }
    return result;
}

BigInt BigInt::operator^(unsigned q)
{
    return power(*this,q);
}

BigInt BigInt::operator^(BigInt b)
{
    if(b==BigInt()) return BigInt(1);
    BigInt result = *this;
    for(BigInt i=BigInt(1); i<b; i=i+1)
    {
        result=*this*result;
    }
    return result;
}
