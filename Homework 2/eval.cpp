//
// Created by Matthew Pombo on 2019-02-05.
//

#include <iostream>
#include <string>
#include <cctype>
#include <stack>
#include <cassert>
#include "Set.h"
using namespace std;

bool validInfix(const string& infix);
bool infixToPostfix(const string& infix, string& postfix);
int precedence(const char& ch);
bool evalPostfix(const string& postfix, const Set& trues, const Set& falses);

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {
    // this first huge block is to convert infix to postfix
    if (!infixToPostfix(infix, postfix))
        return 1;
    else {
        for (int k = 0; k != postfix.size(); k++) {
            char ch = postfix[k];
            // all this says is that ch is contained in one of them, but not both
            if (isalpha(ch)) {
                if ((trueValues.contains(ch) || falseValues.contains(ch))
                    && !(trueValues.contains(ch) && falseValues.contains(ch)))
                    continue;
                else {
                    // ch is not contained in either
                    if (!trueValues.contains(ch) && !falseValues.contains(ch))
                        return 2;
                    if (trueValues.contains(ch) && falseValues.contains(ch))
                        return 3;
                }
            }
        }
        // if it reaches this point, then every character in it is valid
        result = evalPostfix(postfix, trueValues, falseValues);
        return 0;
    }
}

bool validInfix(string infix) {
    string tempNoSpace;
    for (int k = 0; k != infix.size(); k++) {
        if (infix[k] != ' ')
            tempNoSpace += infix[k];
    }
    infix = tempNoSpace;
    // infix now has no spaces and has no invalid characters, makes checks easier
    delete &tempNoSpace;
    for (int k = 0; k != infix.size(); k++) {
        if (! (islower(infix[k]) || infix[k] == '&' || infix[k] == '|' || infix[k] == '!') )
            return false;

    }
}

// return true if it's a valid infix expression, false if not
// it also turns postfix into a postfix expression
bool infixToPostfix(const string& infix, string& postfix) {
    // "ops" means "operators"
    stack<char> ops;
    string post;
    for (size_t k = 0; k != infix.size(); k++) {
        char ch = infix[k];

        // I found it easier to implement this in an if-else block than a switch statement
        if (islower(ch)) {
            post += ch;
        }

        else if (ch == '(') {
            ops.push(ch);
        }

        else if (ch == ')') {
            while (ops.top() != '(') {
                post += ops.top();
                ops.pop();
            }
            ops.pop();
        }

        else if (ch == '!' || ch == '&' || ch == '|') {
            while (!ops.empty() && ops.top() != '(' && precedence(ch) <= precedence(ops.top())) {
                post += ops.top();
                ops.pop();
            }
            ops.push(ch);
        }

        else if (ch == ' ')
            continue;

        else
            return false;
    }
    while (!ops.empty()) {
        post += ops.top();
        ops.pop();
    }
    postfix = post;
    return true;
}

bool evalPostfix(const string& postfix, const Set& trues, const Set& falses) {
    stack<char> operands;
    for (int k = 0; k != postfix.size(); k++) {
        char ch = postfix[k];
        if (isalpha(ch))
            operands.push(ch);

        // unary operator
        else if (ch == '!') {
            char op = operands.top();
            operands.pop();
            char f;
            falses.get(0, f);
            char t;
            trues.get(0, t);
            if (trues.contains(op))
                // push a false value
                operands.push(f);
            else {
                operands.push(t);
            }
        }

        // binary operators
        else if (ch == '&' || ch == '|') {
            char op2 = operands.top();
            operands.pop();
            char op1 = operands.top();
            operands.pop();
            if (ch == '&') {
                if (trues.contains(op1) && trues.contains(op2)) {
                    // op1 will always be true
                    operands.push(op1);
                }
                else {
                    // if it evaluates to false, push the false one onto the stack
                    if (falses.contains(op1)) {
                        operands.push(op1);
                    }
                    else if (falses.contains(op2))
                        operands.push(op2);
                }
            }
            else {
                if (trues.contains(op1) || trues.contains(op2)) {
                    // push the true one onto the stack
                    if (trues.contains(op1))
                        operands.push(op1);
                    else
                        operands.push(op2);
                }
                // otherwise, op1 is guaranteed to be false
                else
                    operands.push(op1);
            }
        }
    }
    char c = operands.top();
    if (trues.contains(c))
        return true;
    else
        return false;
}

// easy way to compare the precedence of characters in infixToPostfix
int precedence(const char& ch) {
    switch (ch) {
        case '|':
            return 1;
        case '&':
            return 2;
        case '!':
            return 3;
        default:
            return 0;
    }
}

int main() {
    string infix = "w| f";
    string trueChars1 = "ucla";
    string falseChars1 = "nsx";
    Set trues1;
    Set falses1;
    for (int k = 0; k != trueChars1.size(); k++) {
        trues1.insert(trueChars1[k]);
    }
    for (int k = 0; k != falseChars1.size(); k++) {
        falses1.insert(falseChars1[k]);
    }
    string postfix;
    bool b = infixToPostfix(infix, postfix);

    if (b) {
        cout << "Postfix expression is: " << postfix << endl;
        bool e = evalPostfix(postfix, trues1, falses1);
        if (e)
            cout << "The expression is TRUE" << endl;
        else
            cout << "The expression is FALSE" << endl;
    }
    else
        cout << "Invalid infix expression!" << endl;
    cout << "======" << endl;
    string trueChars  = "tywz";
    string falseChars = "fnx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);

    string pf;
    bool answer;
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
    //assert(evaluate("y|", trues, falses, pf, answer) == 1);
    //assert(evaluate("n t", trues, falses, pf, answer) == 1);
    //assert(evaluate("nt", trues, falses, pf, answer) == 1);
    //assert(evaluate("()", trues, falses, pf, answer) == 1);
    //assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
    //assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
    //assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
    //assert(evaluate("", trues, falses, pf, answer) == 1);
    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
           &&  pf == "ff!tn&&|"  &&  !answer);
    assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
    trues.insert('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 3);
    falses.erase('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
    trues.erase('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 2);
    falses.insert('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
    cout << "Passed all tests" << endl;
}