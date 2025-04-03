#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include <QWidget>
#include "profilepage.h"
#include "errorlogpage.h"
class HomeScreen;

namespace Ui {
class OptionsScreen;
}

class OptionsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsScreen(HomeScreen *home, QWidget *parent = nullptr);
    ~OptionsScreen();

private slots:
    void on_personalProfilesButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::OptionsScreen *ui;
    ProfilePage *profilePage;
    errorlogpage *errorLogs;
    HomeScreen *homeScreen;


};

#endif // OPTIONSSCREEN_H
