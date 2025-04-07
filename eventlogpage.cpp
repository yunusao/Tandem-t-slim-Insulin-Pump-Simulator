#include "eventlogpage.h"
#include "ui_eventlogpage.h"

EventLogPage::EventLogPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventLogPage)
{
    ui->setupUi(this);
}

EventLogPage::~EventLogPage()
{
    delete ui;
}

void EventLogPage::loadEvents()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT timestamp, eventType, amount, notes FROM AllEvents ORDER BY id DESC");

    model->setHeaderData(0, Qt::Horizontal, "Timestamp");
    model->setHeaderData(1, Qt::Horizontal, "Event Type");
    model->setHeaderData(2, Qt::Horizontal, "Amount");
    model->setHeaderData(3, Qt::Horizontal, "Notes");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void EventLogPage::on_backButton_clicked()
{
    this->hide();
    if (QWidget *parent = parentWidget()) {
        parent->show();
    }
}
