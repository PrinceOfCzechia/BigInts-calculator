#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cmath>
#include "bigInt.h"
#include "bigIntExcpt.h"
#include "evalExcpt.h"

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
    {'u',4},
    {'(',0},
    {')',0}
};

bool isOperator(char c)
{
    if(c=='+' | c=='-' | c=='*' | c=='/' | c =='^' | c=='(' | c==')') return 1;
    return 0;
}

string firstUnary(string input)
{
    string output=(input[0]=='-' ? "0"+input : input);
    return output;
}

string unaryPrep(string input)
{
    string output;
    bool isPrecededByOperator=1;
    for(unsigned i=0; i<input.length(); i++)
    {
        if(isPrecededByOperator && input[i]=='-')
        {
            output.append("u");
        }
        else
        {
            output.append(string(1,input[i]));
        }
        isPrecededByOperator=0;
        if(isOperator(input[i])) isPrecededByOperator=1;
    }
    return output;
}

vector<string> tokenize(string input)
{
    if(input=="") throw EvalException("ERROR: invalid input"); // add exception class or enum
    vector<string> tokens;
    string temp = "";
    for(char c : input)
    {
        if(isdigit(c) || c=='u')
        {
            temp+=c;
        }
        else if(isOperator(c))
        {
            if(temp!="") tokens.push_back(temp);
            temp="";
            tokens.push_back(string(1,c));
        }
        else if(c==' '){}
        else throw EvalException("ERROR: invalid input");
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
        if(isdigit(token[0]) || token[0]=='u')
        {
            RPN.push_back(token); // if the token is a number, push it to the output;
        }
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
    while(!opStack.empty())
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
        if(s[0]=='u')
        {
            if(s.erase(0,1)!="") evalStack.push(BigInt(s));
            else throw EvalException("ERROR: invalid input");
        }
        else if(isOperator(s[0]))
        {
            if(evalStack.empty()) throw EvalException("ERROR: invalid input");
            temp1=BigInt(evalStack.top());
            // std::cout << temp1;
            evalStack.pop();
            if(evalStack.empty()) throw EvalException("ERROR: invalid input");
            temp2=BigInt(evalStack.top());
            // std::cout << temp2;
            evalStack.pop();
            if(s=="+") evalStack.push(temp2+temp1); // note that the order of temp1 and temp2 is switched
            else if (s=="-") evalStack.push(temp2-temp1);
            else if (s=="*") evalStack.push(temp2*temp1);
            else if (s=="^") evalStack.push(temp2^temp1);
            else if (s=="/")
            {
                try
                {
                    evalStack.push(temp2/temp1);
                }
                catch (BigIntException &e)
                {
                    return("ERROR: division by zero");
                }
            }
            // one of the cases certainly happened, since parentheses are not allowed anymore
        }
        else evalStack.push(BigInt(s));
    }
    std::cout << evalStack.top();
    return evalStack.top().shortString();
}
