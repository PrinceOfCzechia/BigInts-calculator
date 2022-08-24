#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cmath>
#include "bigInt.h"
#include "bigIntExcpt.h"

using std::string;
using std::vector;
using std::stack;
using std::unordered_map;

unordered_map<char, int> opMap
{
    {'+',1},
    {'-',1},
    {'*',2},
    {'/',2},
    {'^',3},
    {'(',0},
    {')',0}
};

bool isOperator(char c)
{
    if(c=='+' | c=='-' | c=='*' | c=='/' | c =='^' | c=='(' | c==')') return 1;
    return 0;
}

vector<string> tokenize(string input)
{
    vector<string> tokens;
    string temp = "";
    for(char c : input)
    {
        if(isdigit(c)) temp+=c;
        if(isOperator(c))
        {
            if(temp!="") tokens.push_back(temp);
            temp="";
            tokens.push_back(string(1,c));
        }
        else continue;
    }
    if(temp!="") tokens.push_back(temp); // empty the rest of the input after operators if there is something to empty
    return tokens;
}

vector<string> infix2RPN(vector<string>infix, unordered_map<char, int> opMap)
{
    vector<string> RPN;
    stack<char> opStack;
    for(string token : infix)
    {
        if(isdigit(token[0])) RPN.push_back(token); // if the token is a number, push it to the output;
        if(isOperator(token[0])) // if the token is an opertor, do the shunting yard algorithm
        {
            if(token=="(") opStack.push(token[0]);
            else if(token==")")
            {
                while(opStack.top()!='(')
                {
                    RPN.push_back(string(1,opStack.top())); // put all the operators in brackets in the output vector one by one
                    opStack.pop(); // and pop them afterwards
                }
                opStack.pop(); // pop the reamining parenthesis
            }
            else
            {
                while(!opStack.empty() && opMap[token[0]]<=opMap[opStack.top()])
                {
                    RPN.push_back(string(1,opStack.top()));
                    opStack.pop();
                }
                opStack.push(token[0]);
            }
        }
    }
    while(!opStack.empty()) // empty the operator stack into the output vector
    {
        RPN.push_back(string(1, opStack.top()));
        opStack.pop();
    }
    return RPN;
}

std::string evalRPN(vector<string> RPN)
{
    stack<BigInt> evalStack;
    BigInt temp1;
    BigInt temp2;
    for(string s : RPN)
    {
        if(isOperator(s[0]))
        {
            temp1=BigInt(evalStack.top());
            std::cout << temp1;
            evalStack.pop();
            temp2=BigInt(evalStack.top());
            std::cout << temp2;
            evalStack.pop();
            if(s=="+") evalStack.push(temp2+temp1); // note that the order of temp1 and temp2 is switched
            else if (s=="-") evalStack.push(temp2-temp1);
            else if (s=="*") evalStack.push(temp2*temp1);
            else if (s=="^") evalStack.push(temp2^temp1);
            else if (s=="/")
            {
                evalStack.push(temp2/temp1);
            }
            // one of the cases certainly happened, since parentheses are not allowed anymore
        }
        else evalStack.push(BigInt(s)); // std::stoi, convert string to int since c++11
    }
    std::cout << evalStack.top();
    return evalStack.top().shortString();
}
