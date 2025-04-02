#include "errorlogpage.h"
#include "ui_errorlogpage.h"

/**
 * @brief errorlogpage::errorlogpage
 * @param parent
 */
errorlogpage::errorlogpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::errorlogpage)
{
    qDebug() << "Error"<< QSqlDatabase::database().databaseName();
    ui->setupUi(this);
    loadErrors();
}

errorlogpage::~errorlogpage()
{
    delete ui;
}


void errorlogpage::on_backButton_clicked()
{
    this->hide();
    if ( parentWidget()){
        parentWidget()->show();
    }
}

/**
 * @brief errorlogpage::loadErrors
 *
 * Goes though every item placed in the errorLogs table and presets the value of the
 * correspondding table widget to its db value
 */
void errorlogpage::loadErrors() {
    ui->errorTable->setRowCount(0);
    QSqlQuery q("SELECT * FROM errorLogs");
    int row = 0;
    while(q.next()){
      ui->errorTable->insertRow(row);
      ui->errorTable->setItem(row,0, new QTableWidgetItem(q.value("timestamp").toString()));
      ui->errorTable->setItem(row,1, new QTableWidgetItem(q.value("message").toString()));
      row++;
    }
    ui->errorTable->resizeColumnToContents(0);
    ui->errorTable->resizeColumnToContents(1);
}
