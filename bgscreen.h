#ifndef BGSCREEN_H
#define BGSCREEN_H

#include <QWidget>
#include "correctionsuggestionscreen.h"

namespace Ui {
class bgscreen;
}

class bgscreen : public QWidget
{
    Q_OBJECT

public:
    explicit bgscreen(QWidget *parent = nullptr);
    ~bgscreen();
    void setCorrectionScreen(CorrectionSuggestionScreen *screen);
    void setTargetBG(float value);

private:
    Ui::bgscreen *ui;
    QString bgInput;
    CorrectionSuggestionScreen *correctionScreen;
    float targetBG;

private slots:
    void handleDigit(const QString &digit);
    void clearInput();
    void insertDecimalPoint();
signals:
    void bgEntered(QString value);
};

#endif // BGSCREEN_H
