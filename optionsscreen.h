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
    void updateBasalButtonLabel();  // New helper to set suspend/resume button text


private slots:
    void on_personalProfilesButton_clicked();

    void on_pushButton_clicked();
    void on_suspendResumeButton_clicked();   // New slot for basal toggle button
    void on_eventLogButton_clicked();


private:
    Ui::OptionsScreen *ui;
    ProfilePage *profilePage;
    errorlogpage *errorLogs;
    HomeScreen *homeScreen;


};

#endif // OPTIONSSCREEN_H