// Copyright 2026 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"

int getPriority(const char op) {
  if (op == '(') return 0;
  if (op == ')') return 1;
  if (op == '+' || op == '-') return 2;
  if (op == '*' || op == '/') return 3;
  return -1;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> opStack;
  std::string postfix;

  for (size_t i = 0; i < inf.length(); ++i) {
    char ch = inf[i];
    if (std::isspace(static_cast<unsigned char>(ch))) continue;

    if (std::isdigit(static_cast<unsigned char>(ch))) {
      // Используем do-while, чтобы избежать предупреждения knownConditionTrueFalse
      do {
        postfix += inf[i++];
      } while (i < inf.length() &&
               std::isdigit(static_cast<unsigned char>(inf[i])));
      postfix += ' ';
      i--;  // Корректируем индекс для внешнего цикла for
    } else if (ch == '(') {
      opStack.push(ch);
    } else if (ch == ')') {
      while (!opStack.isEmpty() && opStack.get() != '(') {
        postfix += opStack.get();
        postfix += ' ';
        opStack.pop();
      }
      if (!opStack.isEmpty()) opStack.pop();
    } else {
      int priority = getPriority(ch);
      while (!opStack.isEmpty() && getPriority(opStack.get()) >= priority) {
        postfix += opStack.get();
        postfix += ' ';
        opStack.pop();
      }
      opStack.push(ch);
    }
  }

  while (!opStack.isEmpty()) {
    postfix += opStack.get();
    postfix += ' ';
    opStack.pop();
  }

  if (!postfix.empty() && postfix.back() == ' ') {
    postfix.pop_back();
  }
  return postfix;
}

int eval(const std::string& pref) {
  TStack<int, 100> valStack;

  for (size_t i = 0; i < pref.length(); ++i) {
    if (std::isspace(static_cast<unsigned char>(pref[i]))) continue;

    if (std::isdigit(static_cast<unsigned char>(pref[i]))) {
      std::string num;
      do {
        num += pref[i++];
      } while (i < pref.length() &&
               std::isdigit(static_cast<unsigned char>(pref[i])));
      valStack.push(std::stoi(num));
      i--;
    } else {
      int v2 = valStack.get();
      valStack.pop();
      int v1 = valStack.get();
      valStack.pop();

      if (pref[i] == '+') valStack.push(v1 + v2);
      else if (pref[i] == '-') valStack.push(v1 - v2);
      else if (pref[i] == '*') valStack.push(v1 * v2);
      else if (pref[i] == '/') valStack.push(v1 / v2);
    }
  }
  return valStack.get();
}
