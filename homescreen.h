#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = nullptr);
    ~HomeScreen();

private slots:
    void updateTime(); // Slot to update time and date

private:
    Ui::HomeScreen *ui;
    QTimer *timer; // Timer to trigger time updates
};

#endif // HOMESCREEN_H
