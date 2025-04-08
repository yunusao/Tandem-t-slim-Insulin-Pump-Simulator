#ifndef CREATEEDITPROFILE_H
#define CREATEEDITPROFILE_H

#include "homescreen.h"
#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>

namespace Ui {
class CreateEditProfile;
}

class CreateEditProfile : public QWidget
{
    Q_OBJECT

public:
    explicit CreateEditProfile(QWidget *parent = nullptr, int editProfileId = -1, HomeScreen *home = nullptr);
    ~CreateEditProfile();

private slots:

    void on_submiButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::CreateEditProfile *ui;
    int id;
    HomeScreen *homeScreen = nullptr;


signals:
    void profileSaved();  // ✅ will notify parent to reload
};

#endif // CREATEEDITPROFILE_H
