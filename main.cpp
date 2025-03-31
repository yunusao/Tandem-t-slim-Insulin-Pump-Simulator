#include "mainwindow.h"
#include "homescreen.h"
#include <QApplication>

int main(int argc, char *argv[])
 {
     QApplication a(argc, argv);
     HomeScreen home;
     home.show();
     return a.exec();
 }


