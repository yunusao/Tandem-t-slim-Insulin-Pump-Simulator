#ifndef BGSCREEN_H
#define BGSCREEN_H

#include <QWidget>

namespace Ui {
class bgscreen;
}

class bgscreen : public QWidget
{
    Q_OBJECT

public:
    explicit bgscreen(QWidget *parent = nullptr);
    ~bgscreen();

private:
    Ui::bgscreen *ui;
    QString bgInput;

private slots:
    void handleDigit(const QString &digit);
    void clearInput();
    void toggleSign();
signals:
    void bgEntered(QString value);
};

#endif // BGSCREEN_H
