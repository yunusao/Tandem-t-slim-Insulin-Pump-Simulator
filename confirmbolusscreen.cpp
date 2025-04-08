#include "confirmbolusscreen.h"
#include "ui_confirmbolusscreen.h"
#include "finaldeliveryscreen.h"


ConfirmBolusScreen::ConfirmBolusScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmBolusScreen)
{
    ui->setupUi(this);
    finalDeliveryScreen = new FinalDeliveryScreen(this);  // Make this screen a child
    finalDeliveryScreen->setWindowFlags(Qt::Window);      // ✅ Make it screen-style
    finalDeliveryScreen->hide();

    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        QString units = ui->labelUnitsToDeliver->text();  // get the displayed units
        finalDeliveryScreen->setTotalUnits(units);        // pass to next screen
        finalDeliveryScreen->setFood(units);
        finalDeliveryScreen->setCorrection(correctionValue);
        this->hide();  // Hide this screen
        finalDeliveryScreen->show();  // Show the new one
    });

    connect(ui->cancelButton, &QPushButton::clicked, this, [=]() {
        this->hide();  // ✅ Hide this screen

        if (parentWidget()) {
            parentWidget()->show();  // ✅ Show the BolusScreen
        }
    });
}

ConfirmBolusScreen::~ConfirmBolusScreen()
{
    delete ui;
}

void ConfirmBolusScreen::setCarbs(QString value)
{
    ui->labelCarbsValue->setText(value + " g");
}

void ConfirmBolusScreen::setBG(QString value)
{
    ui->labelBGValue->setText(value + " mmol/L");
}

void ConfirmBolusScreen::setUnits(QString value)
{
    ui->labelUnitsToDeliver->setText(value + " u");
}

void ConfirmBolusScreen::setCorrection(QString value){
    correctionValue = value;
}
