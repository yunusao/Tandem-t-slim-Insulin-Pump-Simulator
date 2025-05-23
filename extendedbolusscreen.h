#ifndef EXTENDEDBOLUSSCREEN_H
#define EXTENDEDBOLUSSCREEN_H

#include <QWidget>
#include "delivernowinputscreen.h"
#include "durationinputscreen.h"
#include "confirmextendedbolusscreen.h"

namespace Ui {
class ExtendedBolusScreen;
}

class ExtendedBolusScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ExtendedBolusScreen(QWidget *parent = nullptr);
    ~ExtendedBolusScreen();

    void setTotalUnits(QString units);

private:
    Ui::ExtendedBolusScreen *ui;
    DeliverNowInputScreen *nowInputScreen;
    DurationInputScreen *durationScreen;
    ConfirmExtendedBolusScreen *confirmExtendedBolusScreen;
};

#endif // EXTENDEDBOLUSSCREEN_H
