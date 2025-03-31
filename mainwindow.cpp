#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->powerOffScreen->show();  // Make sure it's visible at launch
    connect(ui->powerButton, &QPushButton::pressed, this, &MainWindow::powerPressed);
    connect(ui->powerButton, &QPushButton::released, this, &MainWindow::powerReleased);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::powerPressed() {
    pressStartTime = QDateTime::currentDateTime();
}

void MainWindow::powerReleased() {
    int duration = pressStartTime.msecsTo(QDateTime::currentDateTime());
    if (duration >= 3000) {  // 3 seconds
        ui->powerOffScreen->hide();  // Show the main UI
    } else {
        QMessageBox::information(this, "Power", "Hold the power button to turn on.");
    }
}
