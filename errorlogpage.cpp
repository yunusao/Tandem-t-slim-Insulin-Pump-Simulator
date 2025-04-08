#include "errorlogpage.h"
#include "ui_errorlogpage.h"
#include <QSqlQuery>
#include <QDebug>

errorlogpage::errorlogpage(QWidget *parent) : QWidget(parent), ui(new Ui::errorlogpage) {
    ui->setupUi(this);
    // Configure table columns
    ui->errorTable->setColumnCount(2);
    QStringList headers;
    headers << "Timestamp" << "Event";
    ui->errorTable->setHorizontalHeaderLabels(headers);
    ui->errorTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->errorTable->setSelectionMode(QAbstractItemView::NoSelection);
    // Load any existing logs initially
    loadErrors();
}

errorlogpage::~errorlogpage() {
    delete ui;
}

void errorlogpage::loadErrors() {
    ui->errorTable->setRowCount(0);
    QSqlQuery q("SELECT timestamp, message FROM errorLogs ORDER BY id DESC");
    int row = 0;
    while (q.next()) {
        ui->errorTable->insertRow(row);
        QString ts = q.value("timestamp").toString();
        QString msg = q.value("message").toString();
        ui->errorTable->setItem(row, 0, new QTableWidgetItem(ts));
        ui->errorTable->setItem(row, 1, new QTableWidgetItem(msg));
        row++;
    }
    ui->errorTable->resizeColumnToContents(0);
    ui->errorTable->resizeColumnToContents(1);
}

void errorlogpage::on_backButton_clicked() {
    this->hide();
    if (parentWidget()) {
        parentWidget()->show();  // return to OptionsScreen
    }
}