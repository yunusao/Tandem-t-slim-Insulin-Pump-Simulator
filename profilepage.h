#ifndef PROFILEPAGE_H
#define PROFILEPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include "profileservice.h"
#include "homescreen.h"


class HomeScreen;
namespace Ui {
class ProfilePage;

}

class ProfilePage : public QWidget
{
    Q_OBJECT

public:
    explicit ProfilePage(HomeScreen *home = nullptr, QWidget *parent = nullptr);
    ~ProfilePage();
    void loadProfiles();

signals:
    void newActiveProfile();

private slots:
    void on_createProfileButton_clicked();

    void on_backButton_clicked();


private:
    Ui::ProfilePage *ui;
    HomeScreen *homescreen;
};

#endif // PROFILEPAGE_H
