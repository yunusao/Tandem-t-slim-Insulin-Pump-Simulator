#ifndef CORRECTIONSUGGESTIONSCREEN_H
#define CORRECTIONSUGGESTIONSCREEN_H

#include <QWidget>

namespace Ui {
class CorrectionSuggestionScreen;
}

class CorrectionSuggestionScreen : public QWidget
{
    Q_OBJECT

public:
    explicit CorrectionSuggestionScreen(QWidget *parent = nullptr);
    ~CorrectionSuggestionScreen();
    void setBG(QString bg);
    void setIOB(QString iob);

    void setBGMessageBasedOnValue(float bg, float target);

private:
    Ui::CorrectionSuggestionScreen *ui;
    QString bgValueRaw;

signals:
    void correctionConfirmed(QString bgValue);
};

#endif // CORRECTIONSUGGESTIONSCREEN_H
