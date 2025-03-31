#include "carbentryscreen.h"
#include "ui_carbentryscreen.h"

CarbEntryScreen::CarbEntryScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarbEntryScreen)
{
    ui->setupUi(this);
    //Tandem logo button
    connect(ui->homeButton, &QPushButton::clicked, this, [=]() {
        // Hide CarbEntryScreen
        this->hide();

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

    // Connect digit buttons
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

    //Back button
    connect(ui->backButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        parentWidget()->show();  // Show BolusScreen again
    });

    //Check mark button
    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        emit carbsEntered(carbInput);   // Send the value out
        this->hide();                   // Close this screen
        parentWidget()->show();        // Show BolusScreen
    });


}

CarbEntryScreen::~CarbEntryScreen()
{
    delete ui;
}

void CarbEntryScreen::handleDigit(const QString &digit)
{
    if (carbInput == "0") {
        carbInput = digit;
    } else {
        carbInput += digit;
    }

    ui->labelCarbValue->setText(carbInput);
}

void CarbEntryScreen::clearInput()
{
    carbInput = "0";
    ui->labelCarbValue->setText(carbInput);
}

void CarbEntryScreen::toggleSign()
{
    if (carbInput.startsWith("-")) {
        carbInput.remove(0, 1);
    } else if (carbInput != "0") {
        carbInput = "-" + carbInput;
    }
    ui->labelCarbValue->setText(carbInput);
}
