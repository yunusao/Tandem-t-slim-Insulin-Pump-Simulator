#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include <QWidget>
#include "profilepage.h"

namespace Ui {
class OptionsScreen;
}

class OptionsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsScreen(QWidget *parent = nullptr);
    ~OptionsScreen();

private slots:
    void on_personalProfilesButton_clicked();

private:
    Ui::OptionsScreen *ui;
    ProfilePage *profilePage;
};

#endif // OPTIONSSCREEN_H
