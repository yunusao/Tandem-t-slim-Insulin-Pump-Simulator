#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>

#include "bolusscreen.h"
#include "optionsscreen.h"


namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = nullptr);
    ~HomeScreen();

private slots:
    void updateTime(); // Slot to update time and date

    void powerPressed();
    void powerReleased();

    void showBolusScreen();
    void showOptionsScreen();
    void returnHome();

private:
    Ui::HomeScreen *ui;

    QTimer *timer; // Timer to trigger time updates
    QDateTime pressStartTime;

    BolusScreen *bolusScreen;
    OptionsScreen *optionsScreen;
};

#endif // HOMESCREEN_H
