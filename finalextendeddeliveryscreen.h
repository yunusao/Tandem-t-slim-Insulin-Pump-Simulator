#ifndef FINALEXTENDEDDELIVERYSCREEN_H
#define FINALEXTENDEDDELIVERYSCREEN_H

#include <QWidget>
#include "extendedbolusinitiatedscreen.h"

namespace Ui {
class FinalExtendedDeliveryScreen;
}

class FinalExtendedDeliveryScreen : public QWidget
{
    Q_OBJECT

public:
    explicit FinalExtendedDeliveryScreen(QWidget *parent = nullptr);
    ~FinalExtendedDeliveryScreen();

    void setTitle(QString t);
    void setNowCorrection(QString val);
    void setLater(QString val);
    void setDuration(QString val);

private:
    Ui::FinalExtendedDeliveryScreen *ui;
    ExtendedBolusInitiatedScreen *extendedBolusInitiatedScreen;
};

#endif // FINALEXTENDEDDELIVERYSCREEN_H
