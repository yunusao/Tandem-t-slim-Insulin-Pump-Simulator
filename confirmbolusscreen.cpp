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
