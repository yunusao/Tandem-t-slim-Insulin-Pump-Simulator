#ifndef PROFILEPAGE_H
#define PROFILEPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include "profileservice.h"



namespace Ui {
class ProfilePage;
}

class ProfilePage : public QWidget
{
    Q_OBJECT

public:
    explicit ProfilePage(QWidget *parent = nullptr);
    ~ProfilePage();

signals:
    void newActiveProfile();

private slots:
    void on_createProfileButton_clicked();

    void on_backButton_clicked();


private:
    Ui::ProfilePage *ui;
    void loadProfiles();
};

#endif // PROFILEPAGE_H
