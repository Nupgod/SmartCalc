#include "controler.h"

namespace s21 {
double Controller::calc(double x) {
  try {
    return newModel.calculate(x);
  } catch (...) {
    return 777.7;
  }
}
bool Controller::validator(QString infixQt) {
  newModel.clearStr();
  newModel.norminette(infixQt.toStdString());
  newModel.infToPost();
  return newModel.counter();
}
double Controller::annuite_pay(double credit_sum, double percent,
                               double months) {
  return newModel.annuite_pay(credit_sum, percent, months);
}
double Controller::diff_pay_controller(double credit_sum, double percent,
                                       double months, double* monthly_pay_first,
                                       double* last_payment, double* over_pay) {
  return newModel.diff_pay(credit_sum, percent, months, monthly_pay_first,
                           last_payment, over_pay);
}
};  // namespace s21
