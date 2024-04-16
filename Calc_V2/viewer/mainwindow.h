#ifndef SRC_VIEWER_MAINWINDOW_H_
#define SRC_VIEWER_MAINWINDOW_H_

#include <QDoubleValidator>
#include <QMainWindow>
#include <QPrinter>
#include <QVector>

#include "../controller/controler.h"
#include "qcustomplot.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  QVector<double> x, y;
  double credit_sum = 0, percent = 0, months = 0, monthly_pay = 0,
         total_pay = 0, over_pay = 0, first_payment = 0, last_payment = 0,
         X = 0, h = 0, result_for_y = 0, min_x = -5, min_y = -5, max_x = 5,
         max_y = 5;
  std::string type_of_credit;
  s21::Controller NewController;
  bool binaryOper();
  int open = 0;
  double ans = 0;

 private slots:
  void buttons();
  void clearAll();
  void eqvl();
  void graph();
  void on_pushButton_calculate_clicked();
};
#endif  // SRC_VIEWER_MAINWINDOW_H_
