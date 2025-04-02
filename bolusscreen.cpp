#include "bolusscreen.h"
#include "ui_bolusscreen.h"
#include <QInputDialog>
#include "homescreen.h" // To call manualInsulinInjection

BolusScreen::BolusScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BolusScreen)
{
    ui->setupUi(this);
    carbScreen = new CarbEntryScreen(this);  // Parent = BolusScreen
    bgScreen = new bgscreen(this);             // Parent = BolusScreen

    carbScreen->hide();
    bgScreen->hide();

    connect(ui->carbsButton, &QPushButton::clicked, this, &BolusScreen::showCarbEntryScreen);
    connect(ui->bgButton, &QPushButton::clicked, this, &BolusScreen::showBgScreen);

    connect(carbScreen, &CarbEntryScreen::carbsEntered, this, &BolusScreen::updateCarbs);
    connect(bgScreen, &bgscreen::bgEntered, this, &BolusScreen::updateBG);

    // Connect new INSULIN button to manual injection slot
    connect(ui->insulinButton, &QPushButton::clicked, this, &BolusScreen::showInsulinDialog);
}

BolusScreen::~BolusScreen()
{
    delete ui;
}

void BolusScreen::showCarbEntryScreen() {
    this->hide();
    carbScreen->setWindowFlags(Qt::Window);  // Standalone window
    carbScreen->show();
}

void BolusScreen::updateCarbs(QString value)
{
    ui->carbsButton->setText(value + "\n" + "grams");
}

void BolusScreen::showBgScreen() {
    this->hide();
    bgScreen->setWindowFlags(Qt::Window);  // Standalone window
    bgScreen->show();
}

void BolusScreen::updateBG(QString value)
{
    ui->bgButton->setText(value + "\n" + "mmol/L");
}

void BolusScreen::showInsulinDialog() {
    bool ok;
    double insulinAmount = QInputDialog::getDouble(this, "Manual Insulin Delivery",
                                                   "Enter insulin units to deliver:", 0, 0, 300, 1, &ok);
    if (ok) {
         // Get pointer to HomeScreen (parent of BolusScreen)
         HomeScreen* home = qobject_cast<HomeScreen*>(this->parent());
         if (home) {
             home->manualInsulinInjection(insulinAmount);
         }
    }
}

void BolusScreen::on_backButton_clicked()
{
    this->hide();
    if ( parentWidget()){
        parentWidget()->show();
    }
}

