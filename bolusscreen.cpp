#include "bolusscreen.h"
#include "ui_bolusscreen.h"
#include <QInputDialog>
#include "homescreen.h" // To call manualInsulinInjection
#include "correctionsuggestionscreen.h"

BolusScreen::BolusScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BolusScreen)
{
    ui->setupUi(this);
    carbScreen = new CarbEntryScreen(this);  // Parent = BolusScreen
    bgScreen = new bgscreen(this);             // Parent = BolusScreen
    correctionScreen = new CorrectionSuggestionScreen(this);
    confirmBolusScreen = new ConfirmBolusScreen(this);

    carbScreen->hide();
    bgScreen->hide();
    bgScreen->setCorrectionScreen(correctionScreen);
    correctionScreen->hide();
    confirmBolusScreen->hide();

    connect(ui->carbsButton, &QPushButton::clicked, this, &BolusScreen::showCarbEntryScreen);
    connect(ui->bgButton, &QPushButton::clicked, this, &BolusScreen::showBgScreen);

    connect(carbScreen, &CarbEntryScreen::carbsEntered, this, &BolusScreen::updateCarbs);
    connect(bgScreen, &bgscreen::bgEntered, this, &BolusScreen::updateBG);
    connect(correctionScreen, &CorrectionSuggestionScreen::correctionConfirmed, this, &BolusScreen::updateBG);
    connect(ui->confirmButton, &QPushButton::clicked, this, &BolusScreen::showConfirmBolusScreen);

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

void BolusScreen::showConfirmBolusScreen()
{
    QString carbs = ui->carbsButton->text();  // e.g. "38\ngrams"
    QString bg = ui->bgButton->text();        // e.g. "4.5\nmmol/L"

    // Optional: clean up formatting
    QString cleanCarbs = carbs.split("\n").first();  // "38"
    QString cleanBG = bg.split("\n").first();        // "4.5"

    // Hardcoded units to deliver (for now)
    QString units = "3.65";

    confirmBolusScreen->setCarbs(cleanCarbs);
    confirmBolusScreen->setBG(cleanBG);
    confirmBolusScreen->setUnits(units);

    this->hide();
    confirmBolusScreen->setWindowFlags(Qt::Window);
    confirmBolusScreen->show();
}

