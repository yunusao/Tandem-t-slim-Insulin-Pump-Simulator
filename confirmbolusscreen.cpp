#include "confirmbolusscreen.h"
#include "ui_confirmbolusscreen.h"
#include "finaldeliveryscreen.h"

/**
 * @brief ConfirmBolusScreen::ConfirmBolusScreen
 * Constructor: Initializes UI and connects buttons to their respective actions.
 */
ConfirmBolusScreen::ConfirmBolusScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmBolusScreen)
{
    ui->setupUi(this);
    finalDeliveryScreen = new FinalDeliveryScreen(this);    // Make this screen a child
    finalDeliveryScreen->setWindowFlags(Qt::Window);        // Display as a standalone screen
    finalDeliveryScreen->hide();                            // Start hidden

    //Confirm button
    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        QString units = ui->labelUnitsToDeliver->text();            // Retrieve units displayed on screen
               finalDeliveryScreen->setTotalUnits(units);           // Pass units for total bolus
               finalDeliveryScreen->setFood(units);                 // Pass units as food bolus (placeholder)
               finalDeliveryScreen->setCorrection(correctionValue); // Pass correction value
               this->hide();                                        // Hide current screen
               finalDeliveryScreen->show();                         // Show next screen
           });

    //Cancel button
    connect(ui->cancelButton, &QPushButton::clicked, this, [=]() {
        this->hide();

        if (parentWidget()) {
            parentWidget()->show();
        }
    });
}

/**
 * @brief ConfirmBolusScreen::~ConfirmBolusScreen
 * Destructor
 */
ConfirmBolusScreen::~ConfirmBolusScreen()
{
    delete ui;
}

/**
 * @brief ConfirmBolusScreen::setCarbs
 * Updates the displayed carb value.
 * @param value Carbohydrate amount in grams (as string)
 */
void ConfirmBolusScreen::setCarbs(QString value)
{
    ui->labelCarbsValue->setText(value + " g");
}

/**
 * @brief ConfirmBolusScreen::setBG
 * Updates the displayed BG value.
 * @param value Blood glucose level in mmol/L (as string)
 */
void ConfirmBolusScreen::setBG(QString value)
{
    ui->labelBGValue->setText(value + " mmol/L");
}

/**
 * @brief ConfirmBolusScreen::setUnits
 * Sets the total bolus units to deliver.
 * @param value Final recommended dose in units (as string)
 */
void ConfirmBolusScreen::setUnits(QString value)
{
    ui->labelUnitsToDeliver->setText(value + " u");
}

/**
 * @brief ConfirmBolusScreen::setCorrection
 * Stores the correction bolus value to pass to the next screen.
 * @param value Correction dose in units (as string)
 */
void ConfirmBolusScreen::setCorrection(QString value){
    correctionValue = value;
}
