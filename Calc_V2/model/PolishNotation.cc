#include "SmartCalc.h"
namespace s21 {
std::string Model::infToPost() noexcept {
  int opt = 0;
  for (size_t i = 0; i < normalizedInfix.size(); i++) {
    if ((normalizedInfix[i] >= '0' && normalizedInfix[i] <= '9') ||
        normalizedInfix[i] == '.' || normalizedInfix[i] == 'x' ||
        normalizedInfix[i] == 'e') {
      if (normalizedInfix[i] == 'e') {
        postfix += normalizedInfix[i];
        postfix += normalizedInfix[i + 1];
        i += 1;
      } else {
        postfix += normalizedInfix[i];
      }
    } else {
      postfix += ' ';
      if (normalizedInfix[i] == ')') {
        opt = 1;
        popStack(opt);
        opt = 0;
      } else {
        stackLogic(i);
      }
    }
  }
  postfix += ' ';
  popStack(opt);
  deadSpace();
  return postfix;
}

void Model::stackLogic(int index) noexcept {
  if (operands.empty()) {
    operands.push(normalizedInfix[index]);
  } else {
    if (normalizedInfix[index] == '(' ||
        getPrioryty(normalizedInfix[index]) > getPrioryty(operands.top())) {
      operands.push(normalizedInfix[index]);
    } else {
      while (!operands.empty() && operands.top() != '(' &&
             (getPrioryty(normalizedInfix[index]) <=
              getPrioryty(operands.top()))) {
        postfix += operands.top();
        postfix += ' ';
        operands.pop();
      }
      operands.push(normalizedInfix[index]);
    }
  }
}

void Model::popStack(int opt) noexcept {
  if (opt == 1) {
    while (operands.top() != '(') {
      postfix += operands.top();
      postfix += ' ';
      operands.pop();
    }
    operands.pop();
  } else {
    while (!operands.empty()) {
      postfix += operands.top();
      postfix += ' ';
      operands.pop();
    }
  }
}

int Model::getPrioryty(char elem) noexcept {
  int prioryty = -1;
  switch (elem) {
    case '(':
      prioryty = 0;
      break;
    case '+':
    case '-':
      prioryty = 1;
      break;
    case '*':
    case '/':
    case '%':  // mod
      prioryty = 2;
      break;
    case '^':  // pow
    case 'q':  // sqrt
      prioryty = 3;
      break;
    case '~':  // unar minus
      prioryty = 4;
      break;
    case 's':  // sin
    case 'c':  // cos
    case 't':  // tan
    case 'S':  // asin
    case 'C':  // acos
    case 'T':  // atan
    case 'l':  // log
    case 'L':  // ln
      prioryty = 5;
      break;
  }
  return prioryty;
}

void Model::norminette(std::string infix) noexcept {
  for (size_t i = 0; i < infix.size(); i++) {
    if (infix[i] == 'a') {
      if (infix[i + 1] == 's') {
        normalizedInfix += 'S';
        i += 3;
      } else if (infix[i + 1] == 'c') {
        normalizedInfix += 'C';
        i += 3;
      } else {
        normalizedInfix += 'T';
        i += 3;
      }
    } else if (infix[i] == 'c' || infix[i] == 't') {
      normalizedInfix += infix[i];
      i += 2;
    } else if (infix[i] == 'l') {
      if (infix[i + 1] == 'n') {
        normalizedInfix += 'L';
        i += 1;
      } else {
        normalizedInfix += 'l';
        i += 2;
      }
    } else if (infix[i] == 's') {
      if (infix[i + 1] == 'i') {
        normalizedInfix += 's';
        i += 2;
      } else {
        normalizedInfix += 'q';
        i += 3;
      }
    } else if (infix[i] == '-' && (i == 0 || infix[i - 1] == '(')) {
      normalizedInfix += '~';
    } else {
      normalizedInfix += infix[i];
    }
  }
}

void Model::deadSpace() noexcept {
  std::string buff;
  int space = 0;
  for (size_t i = 0; i < postfix.size(); i++) {
    if (postfix[i] == ' ') {
      if (i != 0) {
        if (space == 0) {
          space = 1;
          buff += postfix[i];
        }
      }
    } else {
      space = 0;
      buff += postfix[i];
    }
  }
  postfix = buff;
}
bool Model::counter() noexcept {
  int countNum = 0, oper = 0;
  std::string buff;
  for (size_t i = 0; i <= normalizedInfix.size(); i++) {
    while (((normalizedInfix[i] >= '0' && normalizedInfix[i] <= '9') ||
            (normalizedInfix[i] == '.') || normalizedInfix[i] == 'e' ||
            normalizedInfix[i] == 'x')) {
      buff += normalizedInfix[i];
      if (normalizedInfix[i] == 'e') {
        i++;
        buff += normalizedInfix[i];
      }
      i++;
    }
    std::regex regstr("^[0-9]*[.]?[0-9]+(?:[eE][-+]?[0-9]+)?|x$");
    if (regex_search(buff, regstr)) {
      countNum++;
    }
    buff.clear();
    if (normalizedInfix[i] == '+' || normalizedInfix[i] == '-' ||
        normalizedInfix[i] == '*' || normalizedInfix[i] == '/' ||
        normalizedInfix[i] == '%' || normalizedInfix[i] == '^') {
      oper++;
    }
  }
  buff.clear();
  if (oper == countNum - 1) {
    return true;
  }
  return false;
}

void Model::clearStr() noexcept {
  normalizedInfix.clear();
  postfix.clear();
}
}  // namespace s21
