#ifndef EXTENDEDBOLUSSCREEN_H
#define EXTENDEDBOLUSSCREEN_H

#include <QWidget>

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
};

#endif // EXTENDEDBOLUSSCREEN_H
