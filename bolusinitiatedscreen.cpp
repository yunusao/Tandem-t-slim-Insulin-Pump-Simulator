#include "bolusinitiatedscreen.h"
#include "ui_bolusinitiatedscreen.h"

BolusInitiatedScreen::BolusInitiatedScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BolusInitiatedScreen)
{
    ui->setupUi(this);
    autoCloseTimer = new QTimer(this);

    connect(autoCloseTimer, &QTimer::timeout, this, [=]() {
         autoCloseTimer->stop();
         this->hide();

         // Show HomeScreen if parent is parent-of-parent
         if (parentWidget() && parentWidget()->parentWidget()) {
             parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->show();
         }
     });
}

BolusInitiatedScreen::~BolusInitiatedScreen()
{
    delete ui;
}

void BolusInitiatedScreen::showWithUnits(QString units)
{
    ui->labelUnits->setText(units + " u");
    this->show();
    autoCloseTimer->start(3000);  // 3 seconds
}
