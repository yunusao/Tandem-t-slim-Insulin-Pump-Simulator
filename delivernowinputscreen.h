#ifndef DELIVERNOWINPUTSCREEN_H
#define DELIVERNOWINPUTSCREEN_H

#include <QWidget>

namespace Ui {
class DeliverNowInputScreen;
}

class DeliverNowInputScreen : public QWidget
{
    Q_OBJECT

public:
    explicit DeliverNowInputScreen(QWidget *parent = nullptr);
    ~DeliverNowInputScreen();

private:
    Ui::DeliverNowInputScreen *ui;
    QString percentInput;

private slots:
    void digitClicked(const QString &digit);

signals:
    void percentEntered(QString percent);


};

#endif // DELIVERNOWINPUTSCREEN_H
