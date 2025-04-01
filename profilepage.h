#ifndef PROFILEPAGE_H
#define PROFILEPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QSqlQuery>



namespace Ui {
class ProfilePage;
}

class ProfilePage : public QWidget
{
    Q_OBJECT

public:
    explicit ProfilePage(QWidget *parent = nullptr);
    ~ProfilePage();

private slots:
    void on_createProfileButton_clicked();

private:
    Ui::ProfilePage *ui;
    void loadProfiles();
};

#endif // PROFILEPAGE_H
