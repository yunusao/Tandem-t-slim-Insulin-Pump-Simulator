#include "correctionsuggestionscreen.h"
#include "ui_correctionsuggestionscreen.h"

/**
 * @brief CorrectionSuggestionScreen::CorrectionSuggestionScreen
 * Constructor: Initializes the correction screen UI and connects buttons to handle confirm, cancel, and home.
 */
CorrectionSuggestionScreen::CorrectionSuggestionScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorrectionSuggestionScreen)
{
    ui->setupUi(this);

    //Home Button
    connect(ui->homeButton, &QPushButton::clicked, this, [=]() {
        this->hide();  // Hide CorrectionSuggestionScreen

        if (parentWidget()) {
            parentWidget()->hide();  // Hide BGScreen

            if (parentWidget()->parentWidget()) {
                parentWidget()->parentWidget()->parentWidget()->show();  // Show HomeScreen
            }
        }
    });

    //Confirm button
    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        emit correctionConfirmed(bgValueRaw);

        this->hide();

        if (parentWidget()) {
            parentWidget()->show();  // Show BolusScreen
        }
    });

    // Cancel button
    connect(ui->cancelButton, &QPushButton::clicked, this, [=]() {
        this->hide();  // Hide this screen

        if (parentWidget()) {
            parentWidget()->show();  // Show the BGScreen again
        }
    });


}

/**
 * @brief CorrectionSuggestionScreen::~CorrectionSuggestionScreen
 * Destructor
 */
CorrectionSuggestionScreen::~CorrectionSuggestionScreen()
{
    delete ui;
}

/**
 * @brief CorrectionSuggestionScreen::setBG
 * Sets the displayed BG value and stores raw string value for future use.
 */
void CorrectionSuggestionScreen::setBG(QString bg)
{
    bgValueRaw = bg;
    ui->labelBGValue->setText(bg + " mmol/L");
}

/**
 * @brief CorrectionSuggestionScreen::setIOB
 * Sets the displayed IOB (Insulin On Board) value.
 */
void CorrectionSuggestionScreen::setIOB(QString iob)
{
    ui->labelIOBValue->setText(iob + " u");
}

/**
 * @brief CorrectionSuggestionScreen::setBGMessageBasedOnValue
 * Dynamically changes the suggestion message based on whether BG is above or below the target.
 */
void CorrectionSuggestionScreen::setBGMessageBasedOnValue(float bg, float target)
{
    if (bg < target) {
        ui->labelMessage->setText("Your BG is Below Target\nReduce Bolus Calculation?");
    } else {
        ui->labelMessage->setText("Your BG is Above Target\nAdd Correction Bolus?");
    }
}
