#ifndef EVENTLOGPAGE_H
#define EVENTLOGPAGE_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class EventLogPage;
}

class EventLogPage : public QWidget
{
    Q_OBJECT

public:
    explicit EventLogPage(QWidget *parent = nullptr);
    ~EventLogPage();

    void loadEvents();

private slots:
    void on_backButton_clicked();

private:
    Ui::EventLogPage *ui;
};

#endif // EVENTLOGPAGE_H
