#ifndef EXTENDEDBOLUSINITIATEDSCREEN_H
#define EXTENDEDBOLUSINITIATEDSCREEN_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class ExtendedBolusInitiatedScreen;
}

class ExtendedBolusInitiatedScreen : public QWidget
{
    Q_OBJECT

public:

    explicit ExtendedBolusInitiatedScreen(QWidget *parent = nullptr);
    ~ExtendedBolusInitiatedScreen();
    void showWithValues(QString now, QString later);  // e.g., "2.382", "1.268"

private:
    Ui::ExtendedBolusInitiatedScreen *ui;
    QTimer *autoCloseTimer;
};

#endif // EXTENDEDBOLUSINITIATEDSCREEN_H
