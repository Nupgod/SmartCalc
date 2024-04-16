#include "SmartCalc.h"
namespace s21 {
double Model::annuite_pay(double credit_sum, double percent,
                          double N) noexcept {
  double p = (percent / 100) / 12;
  return (round((credit_sum * (p + (p / (pow((1 + p), N) - 1)))) * 100)) / 100;
}

double Model::diff_pay(double credit_sum, double percent, double N,
                       double *one_pay, double *last_payment,
                       double *over_pay) noexcept {
  *one_pay = credit_sum / N;
  double another_p = percent / 12 / 100;
  double percent_pay = (credit_sum * another_p);
  *over_pay = credit_sum * another_p;
  double all_payings = credit_sum;
  double first_payment = *one_pay + percent_pay;
  for (int i = 0; i < N; i++) {
    credit_sum = credit_sum - *one_pay;
    *over_pay += (credit_sum * another_p);
    percent_pay = (credit_sum * another_p);
    if (credit_sum > 0 && percent_pay > 0.0000001) {
      *last_payment = *one_pay + percent_pay;
    }
  }
  *last_payment = round(*last_payment * 100) / 100;
  *one_pay = round(first_payment * 100) / 100;
  all_payings += *over_pay;
  return all_payings;
}
};  // namespace s21
