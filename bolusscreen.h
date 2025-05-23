#ifndef BOLUSSCREEN_H
#define BOLUSSCREEN_H

#include "carbentryscreen.h"
#include "bgscreen.h"
#include "correctionsuggestionscreen.h"
#include "confirmbolusscreen.h"

#include <QWidget>

namespace Ui {
class BolusScreen;
}

class BolusScreen : public QWidget
{
    Q_OBJECT

public:
    explicit BolusScreen(QWidget *parent = nullptr);
    ~BolusScreen();

private slots:
    void showCarbEntryScreen();
    void showBgScreen();
    void updateCarbs(QString value);
    void updateBG(QString value);
    void showConfirmBolusScreen();
    void showInsulinDialog();  // New slot for manual insulin injection

    void on_backButton_clicked();

private:
    Ui::BolusScreen *ui;
    CarbEntryScreen *carbScreen;
    bgscreen *bgScreen;
    CorrectionSuggestionScreen *correctionScreen;
    ConfirmBolusScreen *confirmBolusScreen;
    //float bgTarget;
};

#endif // BOLUSSCREEN_H
