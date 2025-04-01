#include "optionsscreen.h"
#include "ui_optionsscreen.h"

OptionsScreen::OptionsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsScreen)
{
    ui->setupUi(this);
}

OptionsScreen::~OptionsScreen()
{
    delete ui;
}
