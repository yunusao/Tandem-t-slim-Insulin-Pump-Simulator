#ifndef CONFIRMEXTENDEDBOLUSSCREEN_H
#define CONFIRMEXTENDEDBOLUSSCREEN_H

#include <QWidget>
#include "finalextendeddeliveryscreen.h"

namespace Ui {
class ConfirmExtendedBolusScreen;
}

class ConfirmExtendedBolusScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ConfirmExtendedBolusScreen(QWidget *parent = nullptr);
    ~ConfirmExtendedBolusScreen();
    void setDeliverNow(QString value);
    void setDeliverLater(QString value);
    void setDuration(QString value);
    void setTotalUnits(QString units); // e.g. "3.65"

private:
    Ui::ConfirmExtendedBolusScreen *ui;
    FinalExtendedDeliveryScreen *finalExtendedDeliveryScreen;
    QString totalUnits;
    QString nowPercent;
    QString laterPercent;
    QString duration;
};

#endif // CONFIRMEXTENDEDBOLUSSCREEN_H
