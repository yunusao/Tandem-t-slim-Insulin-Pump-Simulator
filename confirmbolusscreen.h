#ifndef CONFIRMBOLUSSCREEN_H
#define CONFIRMBOLUSSCREEN_H

#include <QWidget>

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

private:
    Ui::ConfirmBolusScreen *ui;
};

#endif // CONFIRMBOLUSSCREEN_H
