#include "extendedbolusinitiatedscreen.h"
#include "ui_extendedbolusinitiatedscreen.h"

ExtendedBolusInitiatedScreen::ExtendedBolusInitiatedScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtendedBolusInitiatedScreen)
{
    ui->setupUi(this);
    autoCloseTimer = new QTimer(this);

        connect(autoCloseTimer, &QTimer::timeout, this, [=]() {
            autoCloseTimer->stop();
            this->hide();

            // Show HomeScreen (assuming 5 parents deep)
            if (parentWidget() && parentWidget()->parentWidget()) {
                parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->show();
            }
        });
}

ExtendedBolusInitiatedScreen::~ExtendedBolusInitiatedScreen()
{
    delete ui;
}

void ExtendedBolusInitiatedScreen::showWithValues(QString now, QString later)
{
    ui->labelUnits->setText(now + " u Now + " + later + " u Later");
    this->show();
    autoCloseTimer->start(3000);  // Show for 3 seconds
}
