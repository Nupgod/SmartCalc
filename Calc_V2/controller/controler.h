#ifndef SRC_CONTROLER_CONTROLER_H
#define SRC_CONTROLER_CONTROLER_H

#include <QString>

#include "../model/SmartCalc.h"

namespace s21 {
class Controller {
 public:
  Controller(){};
  ~Controller(){};
  double calc(double x);
  bool validator(QString infixQt);
  double annuite_pay(double credit_sum, double percent, double months);
  double diff_pay_controller(double credit_sum, double percent, double months,
                             double* monthly_pay_first, double* last_payment,
                             double* over_pay);

 private:
  std::string tot_pay, ov_pay, mon_pay;
  Model newModel;
};
};  // namespace s21

#endif  // SRC_CONTROLER_CONTROLER_H
