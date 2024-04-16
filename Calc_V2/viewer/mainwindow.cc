#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  // numbers
  connect(ui->pushButton_one_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_two_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_three_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_four_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_five_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_six_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_seven_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_eight_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_nine_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_zero_2, SIGNAL(clicked()), this, SLOT(buttons()));
  // E
  connect(ui->pushButton_E_2, SIGNAL(clicked()), this, SLOT(buttons()));
  // X
  connect(ui->pushButton_X_2, SIGNAL(clicked()), this, SLOT(buttons()));
  // Dot
  connect(ui->pushButton_dot_2, SIGNAL(clicked()), this, SLOT(buttons()));
  // CLEAR ALL
  connect(ui->pushButton_CA_2, SIGNAL(clicked()), this, SLOT(clearAll()));
  // close open
  connect(ui->pushButton_close_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_open_2, SIGNAL(clicked()), this, SLOT(buttons()));
  // operands
  connect(ui->pushButton_plus_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_minus_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_mult_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_div_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_mod_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_pow_2, SIGNAL(clicked()), this, SLOT(buttons()));
  // func
  connect(ui->pushButton_sqrt_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_sin_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_cos_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_tan_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_asin_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_acos_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_atan_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_ln_2, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->pushButton_log_2, SIGNAL(clicked()), this, SLOT(buttons()));
  // equal
  connect(ui->pushButton_eqvl_2, SIGNAL(clicked()), this, SLOT(eqvl()));
  // graph
  connect(ui->pushButton_graph_2, SIGNAL(clicked()), this, SLOT(graph()));

  ui->widget_2->xAxis->setRange(-10, 10);
  ui->widget_2->yAxis->setRange(-10, 10);

  // credit
  QLocale lo(QLocale::C);
  lo.setNumberOptions(QLocale::RejectGroupSeparator);
  QDoubleValidator *double_val = new QDoubleValidator(0, 1000000000.0, 6, this);
  double_val->setLocale(lo);
  QIntValidator *int_val = new QIntValidator(1, 100, this);

  QDoubleValidator *for_coordinates =
      new QDoubleValidator(-1000000.0, 1000000.0, 2, this);
  for_coordinates->setLocale(lo);
  ui->minX_2->setValidator(for_coordinates);
  ui->maxX_2->setValidator(for_coordinates);

  ui->minY_2->setValidator(for_coordinates);
  ui->maxY_2->setValidator(for_coordinates);

  ui->month->setValidator(int_val);
  ui->credit_sum->setValidator(double_val);
  connect(ui->pushButton_go, SIGNAL(clicked()), this,
          SLOT(on_pushButton_calculate_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::buttons() {
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == 'E') {
    ui->QLable_expres_2->setText(ui->QLable_expres_2->text() + 'e');
  } else if (button->text() == 'X') {
    ui->QLable_expres_2->setText(ui->QLable_expres_2->text() + 'x');
  } else if (button->text() == "pow" || button->text() == "mod" ||
             button->text() == "+" || button->text() == "*" ||
             button->text() == "/") {
    if (binaryOper() && ui->QLable_expres_2->text().length() > 0) {
      if (button->text() == "pow") {
        ui->QLable_expres_2->setText(ui->QLable_expres_2->text() + '^');
      } else if (button->text() == "mod") {
        ui->QLable_expres_2->setText(ui->QLable_expres_2->text() + '%');
      } else {
        ui->QLable_expres_2->setText(ui->QLable_expres_2->text() +
                                     button->text());
      }
    } else if (button->text() == "+" &&
               ui->QLable_expres_2->text()
                       .toStdString()[ui->QLable_expres_2->text().length() -
                                      1] == 'e') {
      ui->QLable_expres_2->setText(ui->QLable_expres_2->text() +
                                   button->text());
    }
  } else if ((button->text() >= "0" && button->text() <= "9") ||
             button->text() == "." || button->text() == "(") {
    ui->QLable_expres_2->setText(ui->QLable_expres_2->text() + button->text());
    if (button->text() == "(") {
      open++;
    }
  } else if (button->text() == "-" &&
             (binaryOper() || ui->QLable_expres_2->text().length() == 0 ||
              ui->QLable_expres_2->text()
                      .toStdString()[ui->QLable_expres_2->text().length() -
                                     1] == '(' ||
              ui->QLable_expres_2->text()
                      .toStdString()[ui->QLable_expres_2->text().length() -
                                     1] == 'e')) {
    ui->QLable_expres_2->setText(ui->QLable_expres_2->text() + button->text());
  } else if (button->text() == ")" && open > 0 &&
             ui->QLable_expres_2->text()
                     .toStdString()[ui->QLable_expres_2->text().length() - 1] !=
                 '(') {
    ui->QLable_expres_2->setText(ui->QLable_expres_2->text() + button->text());
    open--;
  } else {
    if (button->text().length() > 1 &&
        (ui->QLable_expres_2->text()
                 .toStdString()[ui->QLable_expres_2->text().length() - 1] !=
             'x' &&
         !(ui->QLable_expres_2->text()
                   .toStdString()[ui->QLable_expres_2->text().length() - 1] >=
               '0' &&
           ui->QLable_expres_2->text()
                   .toStdString()[ui->QLable_expres_2->text().length() - 1] <=
               '9'))) {
      ui->QLable_expres_2->setText(ui->QLable_expres_2->text() +
                                   button->text() + '(');
      open++;
    }
  }
}
bool MainWindow::binaryOper() {
  if ((ui->QLable_expres_2->text()
               .toStdString()[ui->QLable_expres_2->text().length() - 1] >=
           '0' &&
       ui->QLable_expres_2->text()
               .toStdString()[ui->QLable_expres_2->text().length() - 1] <=
           '9') ||
      ui->QLable_expres_2->text()
              .toStdString()[ui->QLable_expres_2->text().length() - 1] == 'x' ||
      ui->QLable_expres_2->text()
              .toStdString()[ui->QLable_expres_2->text().length() - 1] == ')') {
    return true;
  }
  return false;
}
void MainWindow::clearAll() {
  ui->QLable_expres_2->setText("");
  ui->Warning_lable_2->setText("");
}

void MainWindow::eqvl() {
  ans = 0;
  ui->Warning_lable_2->setText("");
  if (ui->QLable_expres_2->text().length() < 256) {
    if (NewController.validator(ui->QLable_expres_2->text()) && open == 0) {
      ans = NewController.calc(0);
      if (ans != 777.7) {
        ui->QLable_expres_2->setText(QString::number(ans, 'g', 6));
      } else {
        ui->Warning_lable_2->setText("Invalid num");
      }
    } else {
      ui->Warning_lable_2->setText("Invalid input");
    }
  } else {
    ui->Warning_lable_2->setText("To many symbols");
  }
}

void MainWindow::graph() {
  ui->Warning_lable_2->setText("");
  if (!ui->minX_2->text().isEmpty()) {
    min_x = ui->minX_2->text().toDouble();
  }
  if (!ui->maxX_2->text().isEmpty()) {
    max_x = ui->maxX_2->text().toDouble();
  }
  if (!ui->minY_2->text().isEmpty()) {
    min_y = ui->minY_2->text().toDouble();
  }
  if (!ui->maxY_2->text().isEmpty()) {
    max_y = ui->maxY_2->text().toDouble();
  }

  if (ui->QLable_expres_2->text().length() < 256) {
    if (NewController.validator(ui->QLable_expres_2->text()) && open == 0) {
      if ((min_x >= -1000000 && max_x <= 1000000) &&
          ((min_y >= -1000000 && max_y <= 1000000))) {
        ui->widget_2->clearGraphs();
        x.clear();
        y.clear();
        int graph_num = 0;
        h = 0.001;
        double pace = (fabs(max_x) + fabs(min_x)) / h;
        while (pace > 3000000) {
          h *= 1.2;
          pace = (fabs(max_x) + fabs(min_x)) / h;
        }
        ui->widget_2->xAxis->setRange(min_x, max_x);
        ui->widget_2->yAxis->setRange(min_y, max_y);
        X = min_x;
        while (X < max_x) {
          for (; X < max_x; X += h) {
            if (fabs(X) < 1e-6) {
              result_for_y = NewController.calc(0);
            } else {
              result_for_y = NewController.calc(X);
            }
            if (std::isinf(result_for_y) || std::isnan(result_for_y)) {
              while ((std::isinf(result_for_y) || std::isnan(result_for_y)) &&
                     X < max_x) {
                X += h;
                result_for_y = NewController.calc(X);
              }
              break;
            } else {
              x.push_back(X);
              y.push_back(result_for_y);
            }
            if (result_for_y > 1000000 || result_for_y < -1000000) {
              break;
            }
          }
          ui->widget_2->addGraph();
          ui->widget_2->graph(graph_num)->addData(x, y);
          graph_num += 1;
          x.clear();
          y.clear();
        }
        ui->widget_2->replot();
        x.clear();
        y.clear();
        ui->widget_2->clearGraphs();
      } else {
        ui->Warning_lable_2->setText("Invalid min/max");
      }
    } else {
      ui->Warning_lable_2->setText("Invalid input");
    }
  } else {
    ui->Warning_lable_2->setText("To many symbols");
  }
}

void MainWindow::on_pushButton_calculate_clicked() {
  credit_sum = ui->credit_sum->text().toDouble();
  std::cout << "Credit sum: " << ui->credit_sum->text().toStdString()
            << std::endl;                                  // 13750,78
  std::cout << "Credit sum: " << credit_sum << std::endl;  // 13750,78
  percent = ui->percent_2->value();
  months = ui->month->text().toDouble();
  type_of_credit = ui->credit_type->currentText().toStdString();
  if (type_of_credit == "Аннуитетные") {
    monthly_pay = NewController.annuite_pay(credit_sum, percent, months);
    total_pay = monthly_pay * months;
    over_pay = total_pay - credit_sum;
    ui->total_pay->setText(QString::number(total_pay));
    ui->over_pay->setText(QString::number(over_pay));
    ui->monthly_pay->setText(QString::number(monthly_pay));
  } else {
    total_pay = NewController.diff_pay_controller(
        credit_sum, percent, months, &first_payment, &last_payment, &over_pay);
    ui->total_pay->setText(QString::number(round(total_pay * 100) / 100));
    ui->over_pay->setText(QString::number(round(over_pay * 100) / 100));
    if (months > 1) {
      ui->monthly_pay->setText(QString::number(first_payment) + " ... " +
                               QString::number(last_payment));
    } else {
      ui->monthly_pay->setText(QString::number(first_payment));
    }
  }
}
