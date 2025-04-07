#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include <QWidget>
#include "profilepage.h"
#include "errorlogpage.h"
#include "eventlogpage.h"

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
    void updateToggleInsulinLabel();

private slots:
    void on_personalProfilesButton_clicked();
    void on_pushButton_clicked();
    void on_eventLogButton_clicked();
    void on_toggleInsulinButton_clicked();

private:
    Ui::OptionsScreen *ui;
    ProfilePage *profilePage;
    errorlogpage *errorLogs;
    EventLogPage *eventLogPage;
    HomeScreen *homeScreen;
};

#endif // OPTIONSSCREEN_H
