#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include <QWidget>
#include "profilepage.h"
#include "errorlogpage.h"
#include "eventlogpage.h"


class HomeScreen;
class ProfilePage;

namespace Ui {
class OptionsScreen;
}

class OptionsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsScreen(HomeScreen *home, QWidget *parent = nullptr);
    ~OptionsScreen();
<<<<<<< HEAD
    void updateToggleInsulinLabel();
=======
    void updateBasalButtonLabel();  // New helper to set suspend/resume button text

>>>>>>> iteration-5---jonah

private slots:
    void on_personalProfilesButton_clicked();
    void on_pushButton_clicked();
<<<<<<< HEAD
    void on_eventLogButton_clicked();
    void on_toggleInsulinButton_clicked();
// private stuff
=======
    void on_suspendResumeButton_clicked();   // New slot for basal toggle button
    void on_eventLogButton_clicked();


>>>>>>> iteration-5---jonah
private:
    Ui::OptionsScreen *ui;
    ProfilePage *profilePage;
    errorlogpage *errorLogs;
    EventLogPage *eventLogPage;
    HomeScreen *homeScreen;
};

<<<<<<< HEAD
#endif // OPTIONSSCREEN_H

=======
#endif // OPTIONSSCREEN_H
>>>>>>> iteration-5---jonah
