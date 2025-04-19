#include "confirmdeliveryscreen.h"
#include "ui_confirmdeliveryscreen.h"

/**
 * @brief ConfirmDeliveryScreen::ConfirmDeliveryScreen
 * Constructor: Initializes UI and sets up confirm/cancel logic.
 */
ConfirmDeliveryScreen::ConfirmDeliveryScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmDeliveryScreen)
{
    ui->setupUi(this);

    // Initialize the BolusInitiatedScreen that follows this screen
    bolusScreen = new BolusInitiatedScreen(this);
    bolusScreen->setWindowFlags(Qt::Window);        // Make it appear as a screen
    bolusScreen->hide();                            // Start hidden

    //Cancel button
    connect(ui->cancelButton, &QPushButton::clicked, this, [=]() {
        this->hide();  // Hide this screen

        if (parentWidget()) {
            parentWidget()->show();  // Show FinalDeliveryScreen
        }
    });

    //Confirm button
    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        bolusScreen->showWithUnits(ui->labelTitle->text().split(" ")[1]);  // Extract value like "0.49"
    });

}

/**
 * @brief ConfirmDeliveryScreen::~ConfirmDeliveryScreen
 * Destructor
 */
ConfirmDeliveryScreen::~ConfirmDeliveryScreen()
{
    delete ui;
}

/**
 * @brief ConfirmDeliveryScreen::setUnits
 * Sets the title with the formatted bolus delivery units.
 * @param units String representation of the total units to be delivered
 */
void ConfirmDeliveryScreen::setUnits(QString units)
{
    ui->labelTitle->setText("Deliver " + units + " Bolus?");
}
