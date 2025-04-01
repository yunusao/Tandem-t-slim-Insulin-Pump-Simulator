#include "confirmbolusscreen.h"
#include "ui_confirmbolusscreen.h"

ConfirmBolusScreen::ConfirmBolusScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmBolusScreen)
{
    ui->setupUi(this);
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
