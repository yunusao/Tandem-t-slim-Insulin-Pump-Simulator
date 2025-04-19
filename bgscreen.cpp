#include "bgscreen.h"
#include "ui_bgscreen.h"
#include "correctionsuggestionscreen.h"
#include <QMessageBox>

/**
 * @brief bgscreen::bgscreen
 * Constructor that initializes the BG input screen and connects UI elements to their handlers.
 */
bgscreen::bgscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bgscreen)
{
    ui->setupUi(this);
    bgInput = "0";
    ui->labelBgValue->setText(bgInput);

    // Connect digit buttons (0-9) to handleDigit for dynamic input entry
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

    // Connect clear button to reset the BG input
    connect(ui->btnClear, &QPushButton::clicked, this, &bgscreen::clearInput);

    // Connect decimal button to insert a '.' if not already present
    connect(ui->btnDecimal, &QPushButton::clicked, this, &bgscreen::insertDecimalPoint);

    // Confirm button: validate BG input and show correction screen if needed
    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        bool ok;
        float bgValue = bgInput.toFloat(&ok);

        if (ok) {
            if (bgValue != targetBG) {
                // Show the correction screen if not exactly at target
                correctionScreen->setWindowFlags(Qt::Window);
                correctionScreen->setBG(bgInput);
                correctionScreen->setIOB("0");
                correctionScreen->setBGMessageBasedOnValue(bgValue, targetBG);  // Adjust label message

                correctionScreen->show();
                this->hide();
            } else {
                // If BG matches target, return to parent
                emit bgEntered(bgInput);
                this->hide();
                parentWidget()->show();
            }
        } else {
            QMessageBox::warning(this, "Invalid Input", "Could not interpret BG value.");
        }
    });

    // Back button
    connect(ui->backButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        parentWidget()->show();
    });

    // Tandem logo button
    connect(ui->homeButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        if (parentWidget()) {
            parentWidget()->hide();
            if (parentWidget()->parentWidget()) {
                parentWidget()->parentWidget()->show();
            }
        }
    });

}

/**
 * @brief bgscreen::~bgscreen
 * Destructor
 */
bgscreen::~bgscreen()
{
    delete ui;
}

/**
 * @brief bgscreen::handleDigit
 * Handles digit input by appending to the current BG input.
 * @param digit The digit clicked (0–9)
 */
void bgscreen::handleDigit(const QString &digit)
{
    if (bgInput == "0") {
        bgInput = digit;
    } else {
        bgInput += digit;
    }
    ui->labelBgValue->setText(bgInput);
}

/**
 * @brief bgscreen::clearInput
 * Resets the input to "0"
 */
void bgscreen::clearInput()
{
    bgInput = "0";
    ui->labelBgValue->setText(bgInput);
}

/**
 * @brief bgscreen::insertDecimalPoint
 * Adds a decimal point to the input if not already present
 */
void bgscreen::insertDecimalPoint()
{
    if (!bgInput.contains('.')) {
            if (bgInput.isEmpty()) {
                bgInput = "0.";  // Start with "0." if empty
            } else {
                bgInput += ".";
            }
            ui->labelBgValue->setText(bgInput);
        }
}

/**
 * @brief bgscreen::setCorrectionScreen
 * Passes in a pointer to a shared correction suggestion screen
 * @param screen Pointer to the CorrectionSuggestionScreen instance
 */
void bgscreen::setCorrectionScreen(CorrectionSuggestionScreen *screen) {
    correctionScreen = screen;
}

/**
 * @brief bgscreen::setTargetBG
 * Sets the target BG value to compare against.
 * @param value Target BG value (e.g., 5.0)
 */
void bgscreen::setTargetBG(float value){
    targetBG = value;
}
