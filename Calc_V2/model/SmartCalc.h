#ifndef SRC_MODEL_SMARTCALC_H_
#define SRC_MODEL_SMARTCALC_H_
#include <cmath>
#include <iostream>
#include <regex>
#include <stack>
#include <string>

namespace s21 {
class Model {
 public:
  Model(){};
  ~Model(){};

  // PolishNotation.cpp
  void norminette(std::string infix) noexcept;
  std::string infToPost() noexcept;
  bool counter() noexcept;
  void popStack(int opt) noexcept;
  void stackLogic(int index) noexcept;
  int getPrioryty(char elem) noexcept;
  void deadSpace() noexcept;

  //  Credit.cpp
  double annuite_pay(double credit_sum, double percent, double N) noexcept;
  double diff_pay(double credit_sum, double percent, double N, double *one_pay,
                  double *last_payment, double *over_pay) noexcept;

  // SmartCalc.cpp
  double calculate(double x) noexcept;
  void lexemReader(std::string *buff, int *ind) noexcept;
  void isNum(std::string buff, double x);
  void isUnar(std::string buff) noexcept;
  void isPlus(std::string buff) noexcept;
  void isMinus(std::string buff) noexcept;
  void isMult(std::string buff) noexcept;
  void isDiv(std::string buff) noexcept;
  void isMod(std::string buff) noexcept;
  void isSqrt(std::string buff) noexcept;
  void isPow(std::string buff) noexcept;
  void isLog(std::string buff) noexcept;
  void isLn(std::string buff) noexcept;
  void isSin(std::string buff) noexcept;
  void isAsin(std::string buff) noexcept;
  void isCos(std::string buff) noexcept;
  void isAcos(std::string buff) noexcept;
  void isTan(std::string buff) noexcept;
  void isAtan(std::string buff) noexcept;
  void UnarOp(std::string buff) noexcept;
  void BinaryOp(std::string buff) noexcept;

  void clearStr() noexcept;

 private:
  std::string normalizedInfix, postfix;
  std::stack<char> operands;
  std::stack<double> nums;
};
};      // namespace s21
#endif  // SRC_MODEL_SMARTCALC_H_
