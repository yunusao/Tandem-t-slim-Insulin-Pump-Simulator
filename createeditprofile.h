#ifndef CREATEEDITPROFILE_H
#define CREATEEDITPROFILE_H

#include <QWidget>

namespace Ui {
class CreateEditProfile;
}

class CreateEditProfile : public QWidget
{
    Q_OBJECT

public:
    explicit CreateEditProfile(QWidget *parent = nullptr);
    ~CreateEditProfile();

private:
    Ui::CreateEditProfile *ui;
};

#endif // CREATEEDITPROFILE_H
