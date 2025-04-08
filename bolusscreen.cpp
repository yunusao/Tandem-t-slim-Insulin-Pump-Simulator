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
void BolusScreen::on_backButton_clicked()
{
    this->hide();
    if ( parentWidget()){
        parentWidget()->show();
    }
}
void BolusScreen::showConfirmBolusScreen()
{
    QString carbs = ui->carbsButton->text();  // e.g. "38\ngrams"
    QString bg = ui->bgButton->text();        // e.g. "4.5\nmmol/L"

    // Optional: clean up formatting
    QString cleanCarbs = carbs.split("\n").first();  // "38"
    QString cleanBG = bg.split("\n").first();    // "4.5"

    // Converting input strings to floats.(Ahmid)
    bool okCarbs, okBG;
    float carbValue = cleanCarbs.toFloat(&okCarbs);
    float bgValue = cleanBG.toFloat(&okBG);
    if (!okCarbs) carbValue = 0;
    if (!okBG) bgValue = 0;

    // Retrieve profile parameters or use default values if the profile does not provide them.(Ahmid)
    float ICR = ProfileService::getField(ProfileService::CarbRatio).toFloat();
    if (ICR == 0) ICR = 1;

    float CF = ProfileService::getField(ProfileService::CorrectionFactor).toFloat();
    if (CF == 0) CF = 1;

    float targetBG = ProfileService::getField(ProfileService::GlucoseTarget).toFloat();
    if (targetBG == 0) targetBG = 5;

    float IOB = 5.0; // placeholder based of thr draft list example

    // Calculate the bolus components.(AHmid)
    float carbBolus = carbValue / ICR;

    float correctionBolus = (bgValue > targetBG) ? ((bgValue - targetBG) / CF) : 0;

    float totalBolus = carbBolus + correctionBolus;

    float finalBolus = totalBolus - IOB;

    if (finalBolus < 0) finalBolus = 0; // no negative dose.

    //immediate and extended bolus fractions(60% or 40% based on the draft list example).
    // we need to display this in the appropriate screen
    float immediateBolus = 0.6f * finalBolus;
    float extendedBolus = 0.4f * finalBolus;


    // Format the final recommended bolus dose for display.
    QString recommendedDose = QString::number(finalBolus, 'f', 1);


    // Hardcoded units to deliver (for now) (Ahmid: i replaced this with the recommended dose)
    //QString units = "3.65";

    confirmBolusScreen->setCarbs(cleanCarbs);
    confirmBolusScreen->setBG(cleanBG);
    confirmBolusScreen->setUnits(recommendedDose);

    this->hide();
    confirmBolusScreen->setWindowFlags(Qt::Window);
    confirmBolusScreen->show();
}

