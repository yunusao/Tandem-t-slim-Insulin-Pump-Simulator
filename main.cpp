#include "mainwindow.h"
#include "homescreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Dark Theme Style Sheet
    QString darkStyle = R"(
        /* General widget styling */
        QWidget {
            background-color: #2b2b2b;
            color: #dcdcdc;
            font-family: "Segoe UI", sans-serif;
        }

        /* QLabel styling */
        QLabel {
            color: #dcdcdc;
        }

        /* QLineEdit and QComboBox styling */
        QLineEdit, QComboBox {
            background-color: #3c3f41;
            color: #dcdcdc;
            border: 1px solid #555555;
            padding: 2px;
        }

        /* QPushButton styling */
        QPushButton {
            background-color: #3c3f41;
            color: #dcdcdc;
            border: 1px solid #555555;
            padding: 5px 10px;
            border-radius: 3px;
        }
        QPushButton:hover {
            background-color: #484a4c;
        }
        QPushButton:pressed {
            background-color: #2d2d2d;
        }

        /* QProgressBar styling */
        QProgressBar {
            background-color: #3c3f41;
            border: 1px solid #555555;
            text-align: center;
            color: #dcdcdc;
        }
        QProgressBar::chunk {
            background-color: #0a84ff;
        }

        /* Graph widget styling (assuming it's a QLabel with objectName "graph") */
        QLabel#graph {
            background-color: #1e1e1e;
            border: 1px solid #555555;
        }

        /* QMenu and QMenuBar styling */
        QMenuBar {
            background-color: #3c3f41;
            color: #dcdcdc;
        }
        QMenuBar::item {
            background: transparent;
        }
        QMenuBar::item:selected {
            background: #484a4c;
        }
        QMenu {
            background-color: #3c3f41;
            border: 1px solid #555555;
            color: #dcdcdc;
        }
        QMenu::item:selected {
            background-color: #484a4c;
        }
    )";

    a.setStyleSheet(darkStyle);

    HomeScreen home;
    home.show();
    return a.exec();
}
