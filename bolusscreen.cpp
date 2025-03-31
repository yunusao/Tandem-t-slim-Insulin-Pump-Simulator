#include "bolusscreen.h"
#include "ui_bolusscreen.h"

BolusScreen::BolusScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BolusScreen)
{
    ui->setupUi(this);
    carbScreen = new CarbEntryScreen(this);  // parent = BolusScreen
    bgScreen = new bgscreen(this); // parent = BolusScreen

    carbScreen -> hide();
    bgScreen -> hide();

    connect(ui->carbsButton, &QPushButton::clicked, this, &BolusScreen::showCarbEntryScreen);
    connect(ui->bgButton, &QPushButton::clicked, this, &BolusScreen::showBgScreen);

    connect(carbScreen, &CarbEntryScreen::carbsEntered, this, &BolusScreen::updateCarbs);
    connect(bgScreen, &bgscreen::bgEntered, this, &BolusScreen::updateBG);

}

BolusScreen::~BolusScreen()
{
    delete ui;
}

//Switches to cabEntryScreen.ui page
void BolusScreen::showCarbEntryScreen() {
    this->hide();
    //optionsScreen->show();
    carbScreen->setWindowFlags(Qt::Window);  // Makes it a standalone window
    carbScreen->show();
}

//Updates Carbs Button with input from Entry Screen
void BolusScreen::updateCarbs(QString value)
{
    ui->carbsButton->setText(value + "\n" + "grams");
}

void BolusScreen::showBgScreen() {
    this->hide();
    //optionsScreen->show();
    bgScreen->setWindowFlags(Qt::Window);  // Makes it a standalone window
    bgScreen->show();
}

//Updates Carbs Button with input from Entry Screen
void BolusScreen::updateBG(QString value)
{
    ui->bgButton->setText(value + "\n" + "mmol/L");
}
