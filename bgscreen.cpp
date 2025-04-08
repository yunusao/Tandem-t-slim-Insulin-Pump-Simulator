#include "bgscreen.h"
#include "ui_bgscreen.h"
#include "correctionsuggestionscreen.h"
#include <QMessageBox>  // In case you show warnings

bgscreen::bgscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bgscreen)
{
    ui->setupUi(this);
    bgInput = "0";
    ui->labelBgValue->setText(bgInput);  // Assuming the label is named like this

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


    connect(ui->btnClear, &QPushButton::clicked, this, &bgscreen::clearInput);
    connect(ui->btnDecimal, &QPushButton::clicked, this, &bgscreen::insertDecimalPoint);

    // Confirm
    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        bool ok;
        float bgValue = bgInput.toFloat(&ok);
        //float targetBG = 5.0;  // Can make this dynamic later

        if (ok) {
            if (bgValue != targetBG) {
                // Show the correction screen if not exactly at target
                correctionScreen->setWindowFlags(Qt::Window);
                correctionScreen->setBG(bgInput);
                correctionScreen->setIOB("0");
                correctionScreen->setBGMessageBasedOnValue(bgValue);  // Adjust label message

                correctionScreen->show();
                this->hide();
            } else {
                // Normal case (exactly at target)
                emit bgEntered(bgInput);
                this->hide();
                parentWidget()->show();
            }
        } else {
            QMessageBox::warning(this, "Invalid Input", "Could not interpret BG value.");
        }
    });

    // Back
    connect(ui->backButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        parentWidget()->show();
    });

    // Tandem logo
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

bgscreen::~bgscreen()
{
    delete ui;
}

void bgscreen::handleDigit(const QString &digit)
{
    if (bgInput == "0") {
        bgInput = digit;
    } else {
        bgInput += digit;
    }
    ui->labelBgValue->setText(bgInput);
}

void bgscreen::clearInput()
{
    bgInput = "0";
    ui->labelBgValue->setText(bgInput);
}

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

void bgscreen::setCorrectionScreen(CorrectionSuggestionScreen *screen) {
    correctionScreen = screen;
}

void bgscreen::setTargetBG(float value){
    targetBG = value;
}
