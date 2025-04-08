#ifndef FINALDELIVERYSCREEN_H
#define FINALDELIVERYSCREEN_H

#include <QWidget>
#include "confirmdeliveryscreen.h"
#include "extendedbolusscreen.h"

namespace Ui {
class FinalDeliveryScreen;
}

class FinalDeliveryScreen : public QWidget
{
    Q_OBJECT

public:
    explicit FinalDeliveryScreen(QWidget *parent = nullptr);
    ~FinalDeliveryScreen();
    void setTotalUnits(QString units);  // Pass value like "3.65"
    void setFood(QString value);
    void setCorrection(QString value);

private:
    Ui::FinalDeliveryScreen *ui;
    QString totalUnits;
    QString valueFood;

    void updateTitle();

    ConfirmDeliveryScreen *confirmDeliveryScreen;
    ExtendedBolusScreen *extendedBolusScreen;
};

#endif // FINALDELIVERYSCREEN_H
