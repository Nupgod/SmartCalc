#include <QApplication>
#include <QLocale>

#include "mainwindow.h"
int main(int argc, char *argv[]) {
  QLocale::setDefault(QLocale("en_EN"));
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
