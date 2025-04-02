#include "extendedbolusscreen.h"
#include "ui_extendedbolusscreen.h"

ExtendedBolusScreen::ExtendedBolusScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtendedBolusScreen)
{
    ui->setupUi(this);
}

ExtendedBolusScreen::~ExtendedBolusScreen()
{
    delete ui;
}

void ExtendedBolusScreen::setTotalUnits(QString units)
{
    ui->labelTotalUnits->setText(units);
}
