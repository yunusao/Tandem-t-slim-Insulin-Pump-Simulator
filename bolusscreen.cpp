#include "bolusscreen.h"
#include "ui_bolusscreen.h"
#include <QInputDialog>
#include "homescreen.h" // To call manualInsulinInjection
#include "correctionsuggestionscreen.h"

/**
 * @brief BolusScreen::BolusScreen
 * Constructor: Initializes the bolus screen and connects button actions to their respective slots.
 */
BolusScreen::BolusScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BolusScreen)
{
    ui->setupUi(this);

    // Initialize and hide child screens
    carbScreen = new CarbEntryScreen(this);
    bgScreen = new bgscreen(this);
    correctionScreen = new CorrectionSuggestionScreen(this);
    confirmBolusScreen = new ConfirmBolusScreen(this);

    carbScreen->hide();
    bgScreen->hide();
    correctionScreen->hide();
    confirmBolusScreen->hide();

    // Pass reference to correction screen into bgScreen
    bgScreen->setCorrectionScreen(correctionScreen);

    // Navigation buttons
    connect(ui->carbsButton, &QPushButton::clicked, this, &BolusScreen::showCarbEntryScreen);
    connect(ui->bgButton, &QPushButton::clicked, this, &BolusScreen::showBgScreen);

    // Receive input from child screens
    connect(carbScreen, &CarbEntryScreen::carbsEntered, this, &BolusScreen::updateCarbs);
    connect(bgScreen, &bgscreen::bgEntered, this, &BolusScreen::updateBG);
    connect(correctionScreen, &CorrectionSuggestionScreen::correctionConfirmed, this, &BolusScreen::updateBG);

    // Confirm bolus
    connect(ui->confirmButton, &QPushButton::clicked, this, &BolusScreen::showConfirmBolusScreen);

    // Manual insulin delivery
    connect(ui->insulinButton, &QPushButton::clicked, this, &BolusScreen::showInsulinDialog);
}

/**
 * @brief BolusScreen::~BolusScreen
 * Destructor
 */
BolusScreen::~BolusScreen()
{
    delete ui;
}

/**
 * @brief BolusScreen::showCarbEntryScreen
 * Navigates to the Carb Entry Screen
 */
void BolusScreen::showCarbEntryScreen() {
    this->hide();
    carbScreen->setWindowFlags(Qt::Window);  // Standalone window
    carbScreen->show();
}

/**
 * @brief BolusScreen::updateCarbs
 * Updates the carbsButton label with the user-entered carbohydrate value.
 * @param value Carbs input string
 */
void BolusScreen::updateCarbs(QString value)
{
    ui->carbsButton->setText(value + "\n" + "grams");
}

/**
 * @brief BolusScreen::showBgScreen
 * Navigates to the BG Entry Screen and passes the target BG
 */
void BolusScreen::showBgScreen() {
    this->hide();
    bgScreen->setWindowFlags(Qt::Window);  // Standalone window
    float targetBG = ProfileService::getField(ProfileService::GlucoseTarget).toFloat();
    if (targetBG == 0) targetBG = 5;
    bgScreen->setTargetBG(targetBG);
    bgScreen->show();
}

/**
 * @brief BolusScreen::updateBG
 * Updates the bgButton label with the user-entered blood glucose value.
 * @param value BG input string
 */
void BolusScreen::updateBG(QString value)
{
    ui->bgButton->setText(value + "\n" + "mmol/L");
}

/**
 * @brief BolusScreen::showInsulinDialog
 * Prompts user for manual insulin units to deliver and applies it through HomeScreen.
 */
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

/**
 * @brief BolusScreen::on_backButton_clicked
 * Navigates back to the HomeScreen
 */
void BolusScreen::on_backButton_clicked()
{
    this->hide();
    if ( parentWidget()){
        parentWidget()->show();
    }
}

/**
 * @brief BolusScreen::showConfirmBolusScreen
 * Computes the recommended bolus amount and sends all values to ConfirmBolusScreen.
 */
void BolusScreen::showConfirmBolusScreen()
{
    QString carbs = ui->carbsButton->text();  // e.g. "38\ngrams"
    QString bg = ui->bgButton->text();        // e.g. "4.5\nmmol/L"

    // Optional: clean up formatting
    QString cleanCarbs = carbs.split("\n").first();
    QString cleanBG = bg.split("\n").first();

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

    float correctionBolus = (bgValue > targetBG) ? ((bgValue - targetBG) / CF) : 0; //push this to finalDeliveryScreen

    float totalBolus = carbBolus + correctionBolus;

    float finalBolus = totalBolus - IOB;

    if (finalBolus < 0) finalBolus = 0; // no negative dose.

    //immediate and extended bolus fractions(60% or 40% based on the draft list example).
    // we need to display this in the appropriate screen
    float immediateBolus = 0.6f * finalBolus;
    float extendedBolus = 0.4f * finalBolus;


    // Format the final recommended bolus dose for display.
    QString recommendedDose = QString::number(finalBolus, 'f', 1);
    QString correctionValue = QString::number(correctionBolus,'f',1);

    // Hardcoded units to deliver (for now) (Ahmid: i replaced this with the recommended dose)
    //QString units = "3.65";

    //Pass values to confirm screen
    confirmBolusScreen->setCarbs(cleanCarbs);
    confirmBolusScreen->setBG(cleanBG);
    confirmBolusScreen->setUnits(recommendedDose);
    confirmBolusScreen->setCorrection(correctionValue);

    //Show confirmation screen
    this->hide();
    confirmBolusScreen->setWindowFlags(Qt::Window);
    confirmBolusScreen->show();
}
