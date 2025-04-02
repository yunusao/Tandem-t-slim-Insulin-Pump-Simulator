#ifndef BOLUSINITIATEDSCREEN_H
#define BOLUSINITIATEDSCREEN_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class BolusInitiatedScreen;
}

class BolusInitiatedScreen : public QWidget
{
    Q_OBJECT

public:
    explicit BolusInitiatedScreen(QWidget *parent = nullptr);
    ~BolusInitiatedScreen();

    void showWithUnits(QString units);  // pass "0.49"

private:
    Ui::BolusInitiatedScreen *ui;
    QTimer *autoCloseTimer;
};

#endif // BOLUSINITIATEDSCREEN_H
