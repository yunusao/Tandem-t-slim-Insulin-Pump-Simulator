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

private:
    Ui::ConfirmBolusScreen *ui;
};

#endif // CONFIRMBOLUSSCREEN_H
