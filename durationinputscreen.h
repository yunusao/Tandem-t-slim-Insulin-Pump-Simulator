#ifndef DURATIONINPUTSCREEN_H
#define DURATIONINPUTSCREEN_H

#include <QWidget>

namespace Ui {
class DurationInputScreen;
}

class DurationInputScreen : public QWidget
{
    Q_OBJECT

public:
    explicit DurationInputScreen(QWidget *parent = nullptr);
    ~DurationInputScreen();

private:
    Ui::DurationInputScreen *ui;
    QString rawInput;  // Stores raw 4-digit entry (e.g., "0200")

    void updateDisplay();
    void digitClicked(const QString &digit);
    void updateDigitButtonStates();

signals:
    void durationSet(QString duration);  // emits formatted string like "2:00"
};

#endif // DURATIONINPUTSCREEN_H
