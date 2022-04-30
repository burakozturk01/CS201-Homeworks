#include <iostream>
#include "StrangeCalculator.h"

using namespace std;

string StrangeCalculator::infix2prefix(const string exp) {
    int i,j=0;

    CharStack s;
    char c, tmp1, tmp2;

    string infix = exp;  // To have a mutable copy
    string prefix = exp; // To have the same length as infix

    int N = infix.length();

    // Count of parantheses in original infix
    int brackets = countBrackets(infix);

    s.push('#'); // Anchor is not really needed
                 // but it made it easier for me to plan the algorithm

    reverseStr(infix);

    for (i = 0; i < N; i++) {
        // Scan chars one by one as c
        c = infix[i];

        // If c is an operand, add it to prefix
        if (!isOperator(c)) {
            prefix[j++] = c;
        }
        // If c is an operator or ( , ),
        else {
            // if c is ), push c to stack
            if (c == ')')
                s.push(c);
            // if c is (, start transferring from stack
            //to prefix until finding a ( in stack
            else if (c == '(') {
                s.getTop(tmp1);
                while (tmp1 != ')') {
                    s.pop(tmp2);
                    prefix[j] = tmp2;
                    j++;
                    s.getTop(tmp1);
                }
                s.pop(); // Pop ) from stack
            }
            // if c is an operator, compare top of stack and c
            else {
                // if c has higher or equal precedence, push c to stack
                s.getTop(tmp1);
                if (prec(tmp1) <= prec(c))
                    s.push(c);
                // while top of stack has higher precedence
                // transfer from stack to prefix
                else {
                    s.getTop(tmp1);
                    while (prec(tmp1) > prec(c)) {
                        s.pop(tmp2);
                        prefix[j] = tmp2;
                        j++;
                        s.getTop(tmp1);
                    }
                    s.push(c); // Push operator c to stack
                }
            }
        }
    }
    // Transfer from stack to prefix until hit to anchor #
    // This will achieve reversed prefix
    s.getTop(tmp1);
    while (tmp1 != '#') {
        s.pop(tmp2);
        prefix[j] = tmp2;
        j++;
        s.getTop(tmp1);
    }
    reverseStr(prefix); // Now prefix is straight

    // Cut first [count of parantheses in original infix] characters
    // to get rid of left over characters from the head of the string
    prefix = prefix.substr(brackets, prefix.length() - brackets);
    return prefix;
}

double StrangeCalculator::evaluatePrefix(const string exp) {
    DoubleStack s;

    char c;
    double tmp1, tmp2;

    for (int i = exp.length() - 1; i >= 0; i--) {
        // Scan chars from tail as c
        c = exp[i];
        // If c is operator, pop two numbers from stack
        // process them according to c and push result back
        if (isOperator(c)) {
            s.pop(tmp1); s.pop(tmp2);
            switch (c) {
            case '+':
                s.push(tmp1 + tmp2);
                break;
            case '-':
                s.push(tmp1 - tmp2);
                break;
            case '*':
                s.push(tmp1 * tmp2);
                break;
            case '/':
                s.push(tmp1 / tmp2);
                break;
            }
        }
        // If operand, push to stack
        else {
            s.push((int)(c - '0'));
        }
    }
    // Top of the stack is result, return it
    s.pop(tmp1);
    return tmp1;
}

bool StrangeCalculator::isBalancedInfix(const string exp) {
    CharStack s;

    // Scan chars as c
    for (int i = 0; i < exp.length(); i++) {
        // If it's (, push it to stack
        if (exp[i] == '(') {
            s.push(exp[i]);
        }
        // If it's ), try pop from stack.
        // Can -> Next char | Can't -> unbalanced
        else if (exp[i] == ')') {
            if (!s.pop())
                return false;
        }
    }
    // If stack is empty, all ('s had )'s after them
    return s.isEmpty();
}

void StrangeCalculator::evaluateInputPrefixExpression() {
    string infix = "", tmp;
    cout << "Please enter an infix mathematical expression: ";
    getline(cin, tmp);

    // Filtering out spaces
    for (int i = 0; i < tmp.length(); i++)
        if (tmp[i] != ' ')
            infix += tmp[i];

    if (!isBalancedInfix(infix)) {
        cout << "Your input expression's parantheses are not balanced.\n";
        return;
    }

    string prefix = infix2prefix(infix);

    double result = evaluatePrefix(prefix);

    cout << result;
}
// Swaps chars symmetrically
void StrangeCalculator::reverseStr(string& str) {
    int N = str.length();
    for (int i = 0; i < N/2; i++)
        swap(str[i], str[N-i-1]);
}

// Operators: +-*/()
// Operands : 1234567890 (for all 4 methods)
bool StrangeCalculator::isOperator(const char symbol) {
    switch (symbol) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
            return true; break;
        default:
            return false;
    }
}

//  For order of precedence
int StrangeCalculator::prec(const char symbol) {
    switch (symbol) {
        case '#':
        case '(':
        case ')':
            return 1; break;
        case '+':
        case '-':
            return 2; break;
        case '*':
        case '/':
            return 3; break;
    }
}

int StrangeCalculator::countBrackets(const string infix) {
    int N = infix.length();
    int pCount = 0;
    for (int i = 0; i < N; i++)
        if (infix[i] == '(' || infix[i] == ')')
            pCount++;
    return pCount;
}


