# BigInts-calculator

A calculator built on arithmetics of BigInt type objects defined in my repository ['BigInts-library'](https://github.com/PrinceOfCzechia/BigInts-library). Also a school project for the subject C++ programming 2, as taught at Faculty of Nuclear Sciences and Physical Engineering (FNSPE), Czech Technical University (CTU) Prague.

This calculator implements arithmetic operations (integer addition, subtraction, multiplication, division and powering) on custom type [BigInt](https://github.com/PrinceOfCzechia/BigInts-library). This allows for such operations, as adding *1* to the maximum size of *long long int* and getting a reasonable answer, as is presented in the enclosed image.

<img src="https://user-images.githubusercontent.com/72036926/186395384-a9c65216-aed6-416f-ac45-86b036f5de42.png" height="600"/>

## How it works?

The key components of this calculator are functions inside the file *eval.cpp*. In the following paragraphs, I will briefly describe them:

### tokenize

This function gets a *std::string* as its input and returns a *vector* of *string*s, which contains numbers and operators as separate element. Spaces and other unwanted characters are discarded.

### infix2RPN

This one converts a *vector* of tokens in infix form to a *vector* of those same tokens, but in such order, that they now form a postfix expression. This is achieved via an implementation of Dijkstra's [shunting yard algorithm](https://en.wikipedia.org/wiki/Shunting_yard_algorithm).

### evalRPN

Here, the reverse polish notation vector is evaluated. The algorithm goes as follows

```
while there are tokens to be read:
    read a token, if the token is:
        a number:
          push it to the evaluation stack
        an operator:
          pop two elements from the stack
          calculate the respective operation
          push the result onto the stack
return top of the stack
```

## Exception handling
Attempted division by zero results in an error message in the calculator line. The history above this line keeps the expression which caused this error.

<img src="https://user-images.githubusercontent.com/72036926/186427164-9fba72fe-bd45-40d3-b0fd-b5816a941545.png" width="600"/>

In case of mismatch parentheses, the program adds left parentheses to the very left or right parentheses to the very right of the input line, so that the number of parentheses matches and the expression can be evaluated. This can of course affect the result. I do not handle this in any direct way, but the user can check a their last calculation in the history line above the input/result line.
