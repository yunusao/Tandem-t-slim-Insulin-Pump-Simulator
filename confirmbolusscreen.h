#ifndef CONFIRMBOLUSSCREEN_H
#define CONFIRMBOLUSSCREEN_H

#include <QWidget>
#include "finaldeliveryscreen.h"


namespace Ui {
class ConfirmBolusScreen;
}

class ConfirmBolusScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ConfirmBolusScreen(QWidget *parent = nullptr);
    ~ConfirmBolusScreen();
    void setCarbs(QString value);
    void setBG(QString value);
    void setUnits(QString value);
    void setCorrection(QString value);

private:
    Ui::ConfirmBolusScreen *ui;
    FinalDeliveryScreen *finalDeliveryScreen;
    QString correctionValue;
};

#endif // CONFIRMBOLUSSCREEN_H
