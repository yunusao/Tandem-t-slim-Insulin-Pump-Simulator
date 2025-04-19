#include "carbentryscreen.h"
#include "ui_carbentryscreen.h"

/**
 * @brief CarbEntryScreen::CarbEntryScreen
 * Constructor: Initializes the Carb Entry Screen and sets up UI interactions.
 */
CarbEntryScreen::CarbEntryScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarbEntryScreen)
{
    ui->setupUi(this);
    //Tandem logo button
    connect(ui->homeButton, &QPushButton::clicked, this, [=]() {

        this->hide();       // Hide CarbEntryScreen

        // Hide BolusScreen (parent)
        if (parentWidget()) {
            parentWidget()->hide();

            // Show HomeScreen (grandparent)
            if (parentWidget()->parentWidget()) {
                parentWidget()->parentWidget()->show();
            }
        }
    });

    carbInput = "0";
    ui->labelCarbValue->setText(carbInput);

    // Connect digit buttons (0–9) to handler
    connect(ui->btn0, &QPushButton::clicked, this, [=]() { handleDigit("0"); });
    connect(ui->btn1, &QPushButton::clicked, this, [=]() { handleDigit("1"); });
    connect(ui->btn2, &QPushButton::clicked, this, [=]() { handleDigit("2"); });
    connect(ui->btn3, &QPushButton::clicked, this, [=]() { handleDigit("3"); });
    connect(ui->btn4, &QPushButton::clicked, this, [=]() { handleDigit("4"); });
    connect(ui->btn5, &QPushButton::clicked, this, [=]() { handleDigit("5"); });
    connect(ui->btn6, &QPushButton::clicked, this, [=]() { handleDigit("6"); });
    connect(ui->btn7, &QPushButton::clicked, this, [=]() { handleDigit("7"); });
    connect(ui->btn8, &QPushButton::clicked, this, [=]() { handleDigit("8"); });
    connect(ui->btn9, &QPushButton::clicked, this, [=]() { handleDigit("9"); });

    // Clear and +/- buttons
    connect(ui->btnClear, &QPushButton::clicked, this, &CarbEntryScreen::clearInput);
    connect(ui->btnPlusMinus, &QPushButton::clicked, this, &CarbEntryScreen::toggleSign);

    // Back button: return to BolusScreen
    connect(ui->backButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        parentWidget()->show();  // Show BolusScreen again
    });

    // Confirm button: emit entered carbs and go back to BolusScreen
    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        emit carbsEntered(carbInput);   // Send the value out
        this->hide();                   // Close this screen
        parentWidget()->show();        // Show BolusScreen
    });


}

/**
 * @brief CarbEntryScreen::~CarbEntryScreen
 * Destructor
 */
CarbEntryScreen::~CarbEntryScreen()
{
    delete ui;
}

/**
 * @brief CarbEntryScreen::handleDigit
 * Appends digits to the carb input display.
 * @param digit Pressed digit button as QString
 */
void CarbEntryScreen::handleDigit(const QString &digit)
{
    if (carbInput == "0") {
        carbInput = digit;
    } else {
        carbInput += digit;
    }

    ui->labelCarbValue->setText(carbInput);
}

/**
 * @brief CarbEntryScreen::clearInput
 * Resets the carb input to zero.
 */
void CarbEntryScreen::clearInput()
{
    carbInput = "0";
    ui->labelCarbValue->setText(carbInput);
}

/**
 * @brief CarbEntryScreen::toggleSign
 * Allows toggling the sign (positive/negative) of the carb input.
 */
void CarbEntryScreen::toggleSign()
{
    if (carbInput.startsWith("-")) {
        carbInput.remove(0, 1);
    } else if (carbInput != "0") {
        carbInput = "-" + carbInput;
    }
    ui->labelCarbValue->setText(carbInput);
}
