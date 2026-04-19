// Copyright 2026 NNTU-CS
#include <iostream>
#include <string>
#include <map>
#include "tstack.h"

int getPriority(const char op) {
    if (op == '(')
        return 0;
    else if (op == ')')
        return 1;
    else if (op == '+' || op == '-')
        return 2;
    else if (op == '*' || op == '/')
        return 3;
    else
        throw "Error symbol";
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> opStack;
    int i = 0;
    std::string postfix;

    while (i < inf.length()) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            while (i < inf.length() && inf[i] >= '0' && inf[i] <= '9') {
                postfix += inf[i];
                i++;
            }
            postfix += ' ';
            continue;
        }

        int priority = getPriority(inf[i]);

        if (priority == 0) { 
            opStack.push(inf[i]);
        } 
        else if (priority == 1) { 
            while (!opStack.isEmpty() && getPriority(opStack.get()) != 0) {
                postfix += opStack.get();
                postfix += ' ';
                opStack.pop();
            }
            opStack.pop(); // Удаляем '('
        } 
        else if (priority > 1) { // Операторы +, -, *, /
            if (opStack.isEmpty() || priority > getPriority(opStack.get())) {
                opStack.push(inf[i]);
            } else {
                while (!opStack.isEmpty() && opStack.get() != '(' &&
                       priority <= getPriority(opStack.get())) {
                    postfix += opStack.get();
                    postfix += ' ';
                    opStack.pop();
                }
                opStack.push(inf[i]);
            }
        }
        i++;
    }

    while (!opStack.isEmpty()) {
        postfix += opStack.get();
        postfix += ' ';
        opStack.pop();
    }
    return postfix;
}

int eval(const std::string& pref) {
    TStack<int, 100> valStack;
    int currentRes = 0;
    int pos = 0;

    while (pos < pref.length()) {
        if (pref[pos] >= '0' && pref[pos] <= '9') {
            std::string numberStr;
            while (pref[pos] != ' ') {
                numberStr += pref[pos];
                pos++;
            }
            pos++;
            valStack.push(std::stoi(numberStr));
            continue;
        }
        
        currentRes = valStack.get();
        valStack.pop();
        if (pref[pos] == '+') { 
            currentRes += valStack.get();
        } else if (pref[pos] == '-') {
            currentRes = valStack.get() - currentRes;
        } else if (pref[pos] == '*') {
            currentRes *= valStack.get();
        } else if (pref[pos] == '/') {
            currentRes = valStack.get() / currentRes;
        }
        valStack.pop();
        valStack.push(currentRes);
        currentRes = 0;
        pos += 2;
    }
    return valStack.get();
}
