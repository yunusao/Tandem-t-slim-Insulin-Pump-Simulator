#ifndef CARBENTRYSCREEN_H
#define CARBENTRYSCREEN_H

#include <QWidget>

namespace Ui {
class CarbEntryScreen;
}

class CarbEntryScreen : public QWidget
{
    Q_OBJECT

public:
    explicit CarbEntryScreen(QWidget *parent = nullptr);
    ~CarbEntryScreen();

private:
    Ui::CarbEntryScreen *ui;
    QString carbInput;

    void handleDigit(const QString &digit);
    void clearInput();
    void toggleSign();

 signals:
    void carbsEntered(QString carbValue);
};

#endif // CARBENTRYSCREEN_H
