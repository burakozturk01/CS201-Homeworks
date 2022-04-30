#ifndef SCalH
#define SCalH

#include <iostream>
#include "CharStack.h"
#include "DoubleStack.h"
using namespace std;

// In this shape, functions can't be called without an instance,
// so example driver file wouldn't work.

// I didn't make functions static to use exactly what I was given
// in homework pdf but I didn't use any OOP-only feature.

class StrangeCalculator {
    public:
        string infix2prefix(const string exp);
        double evaluatePrefix(const string exp);

        bool isBalancedInfix(const string exp);
        void evaluateInputPrefixExpression();
    private:
        void reverseStr(string& str);
        bool isOperator(const char symbol);
        int prec(const char symbol);
        int countBrackets(const string infix);
};

#endif // SCalH
