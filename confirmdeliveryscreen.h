#ifndef CONFIRMDELIVERYSCREEN_H
#define CONFIRMDELIVERYSCREEN_H

#include <QWidget>
#include "bolusinitiatedscreen.h"

namespace Ui {
class ConfirmDeliveryScreen;
}

class ConfirmDeliveryScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ConfirmDeliveryScreen(QWidget *parent = nullptr);
    ~ConfirmDeliveryScreen();
    void setUnits(QString units);

private:
    Ui::ConfirmDeliveryScreen *ui;
    BolusInitiatedScreen *bolusScreen;
};

#endif // CONFIRMDELIVERYSCREEN_H
