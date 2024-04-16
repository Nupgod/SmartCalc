#include "SmartCalc.h"
namespace s21 {

double Model::calculate(double x) noexcept {
  std::string buff;
  int index = 0;
  double res = 0;
  while ((size_t)index < postfix.length()) {
    buff.clear();
    lexemReader(&buff, &index);
    isNum(buff, x);
    UnarOp(buff);
    BinaryOp(buff);
  }
  res = nums.top();
  nums.pop();
  return res;
}

void Model::lexemReader(std::string *buff, int *ind) noexcept {
  while (postfix[*ind] != ' ') {
    *buff += postfix[*ind];
    *ind += 1;
  }
  *ind += 1;
}
void Model::UnarOp(std::string buff) noexcept {
  isUnar(buff);
  isMod(buff);
  isSqrt(buff);
  isPow(buff);
  isLog(buff);
  isLn(buff);
  isSin(buff);
  isAsin(buff);
  isCos(buff);
  isAcos(buff);
  isTan(buff);
  isAtan(buff);
}
void Model::BinaryOp(std::string buff) noexcept {
  isPlus(buff);
  isMinus(buff);
  isMult(buff);
  isDiv(buff);
}
void Model::isNum(std::string buff, double x) {
  if ((buff[0] >= '0' && buff[0] <= '9') || buff[0] == 'x') {
    if (buff[0] == 'x') {
      nums.push(x);
    } else {
      nums.push(std::stod(buff));
    }
  }
}

void Model::isUnar(std::string buff) noexcept {
  if (buff[0] == '~') {
    double num1 = 0;
    num1 = nums.top();
    nums.pop();
    nums.push(-num1);
  }
}

void Model::isPlus(std::string buff) noexcept {
  if (buff[0] == '+') {
    double num1 = 0, num2 = 0;
    num1 = nums.top();
    nums.pop();
    num2 = nums.top();
    nums.pop();
    nums.push(num2 + num1);
  }
}

void Model::isMinus(std::string buff) noexcept {
  if (buff[0] == '-') {
    double num1 = 0, num2 = 0;
    num1 = nums.top();
    nums.pop();
    num2 = nums.top();
    nums.pop();
    nums.push(num2 - num1);
  }
}

void Model::isMult(std::string buff) noexcept {
  if (buff[0] == '*') {
    double num1 = 0, num2 = 0;
    num1 = nums.top();
    nums.pop();
    num2 = nums.top();
    nums.pop();
    nums.push(num1 * num2);
  }
}

void Model::isDiv(std::string buff) noexcept {
  if (buff[0] == '/') {
    double num1 = 0, num2 = 0;
    num1 = nums.top();
    nums.pop();
    num2 = nums.top();
    nums.pop();
    nums.push(num2 / num1);
  }
}

void Model::isMod(std::string buff) noexcept {
  if (buff[0] == '%') {
    double num1 = 0, num2 = 0;
    num1 = nums.top();
    nums.pop();
    num2 = nums.top();
    nums.pop();
    nums.push(fmod(num2, num1));
  }
}

void Model::isSqrt(std::string buff) noexcept {
  if (buff[0] == 'q') {
    double num1 = 0;
    num1 = nums.top();
    nums.pop();
    nums.push(sqrt(num1));
  }
}

void Model::isPow(std::string buff) noexcept {
  if (buff[0] == '^') {
    double num1 = 0, num2 = 0;
    num1 = nums.top();
    nums.pop();
    num2 = nums.top();
    nums.pop();
    nums.push(pow(num2, num1));
  }
}

void Model::isSin(std::string buff) noexcept {
  if (buff[0] == 's') {
    double num1 = 0;
    num1 = nums.top();
    nums.pop();
    nums.push(sin(num1));
  }
}
void Model::isCos(std::string buff) noexcept {
  if (buff[0] == 'c') {
    double num1 = 0;
    num1 = nums.top();
    nums.pop();
    nums.push(cos(num1));
  }
}
void Model::isTan(std::string buff) noexcept {
  if (buff[0] == 't') {
    double num1 = 0;
    num1 = nums.top();
    nums.pop();
    nums.push(tan(num1));
  }
}
void Model::isAsin(std::string buff) noexcept {
  if (buff[0] == 'S') {
    double num1 = 0;
    num1 = nums.top();
    nums.pop();
    nums.push(asin(num1));
  }
}
void Model::isAcos(std::string buff) noexcept {
  if (buff[0] == 'C') {
    double num1 = 0;
    num1 = nums.top();
    nums.pop();
    nums.push(acos(num1));
  }
}
void Model::isAtan(std::string buff) noexcept {
  if (buff[0] == 'T') {
    double num1 = 0;
    num1 = nums.top();
    nums.pop();
    nums.push(atan(num1));
  }
}
void Model::isLog(std::string buff) noexcept {
  if (buff[0] == 'l') {
    double num1 = 0;
    num1 = nums.top();
    nums.pop();
    nums.push(log10(num1));
  }
}
void Model::isLn(std::string buff) noexcept {
  if (buff[0] == 'L') {
    double num1 = 0;
    num1 = nums.top();
    nums.pop();
    nums.push(log(num1));
  }
}
};  // namespace s21
