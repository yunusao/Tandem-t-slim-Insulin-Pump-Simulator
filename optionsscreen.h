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

private slots:
    void on_personalProfilesButton_clicked();
    void on_pushButton_clicked();           // Error log button
    void on_eventLogButton_clicked();       // AllEvents log button

private:
    Ui::OptionsScreen *ui;
    ProfilePage *profilePage;
    errorlogpage *errorLogs;
    EventLogPage *eventLogPage;
    HomeScreen *homeScreen;
};

#endif // OPTIONSSCREEN_H
