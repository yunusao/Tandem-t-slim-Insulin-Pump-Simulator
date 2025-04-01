#ifndef CREATEEDITPROFILE_H
#define CREATEEDITPROFILE_H

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
    explicit CreateEditProfile(QWidget *parent = nullptr, int id = -1);
    ~CreateEditProfile();

private slots:

    void on_submiButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::CreateEditProfile *ui;
    int id;

signals:
    void profileSaved();  // ✅ will notify parent to reload
};

#endif // CREATEEDITPROFILE_H
