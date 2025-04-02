#include "durationinputscreen.h"
#include "ui_durationinputscreen.h"

DurationInputScreen::DurationInputScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DurationInputScreen)
{
    ui->setupUi(this);
    updateDigitButtonStates();

    connect(ui->btn0, &QPushButton::clicked, this, [=]() { digitClicked("0"); });
    connect(ui->btn1, &QPushButton::clicked, this, [=]() { digitClicked("1"); });
    connect(ui->btn2, &QPushButton::clicked, this, [=]() { digitClicked("2"); });
    connect(ui->btn3, &QPushButton::clicked, this, [=]() { digitClicked("3"); });
    connect(ui->btn4, &QPushButton::clicked, this, [=]() { digitClicked("4"); });
    connect(ui->btn5, &QPushButton::clicked, this, [=]() { digitClicked("5"); });
    connect(ui->btn6, &QPushButton::clicked, this, [=]() { digitClicked("6"); });
    connect(ui->btn7, &QPushButton::clicked, this, [=]() { digitClicked("7"); });
    connect(ui->btn8, &QPushButton::clicked, this, [=]() { digitClicked("8"); });
    connect(ui->btn9, &QPushButton::clicked, this, [=]() { digitClicked("9"); });

    connect(ui->clearButton, &QPushButton::clicked, this, [=]() {
        rawInput.clear();
        updateDisplay();
        updateDigitButtonStates();  // 👈 reset state
    });

    connect(ui->backButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        if (parentWidget()) parentWidget()->show();
    });

    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        QString padded = rawInput.rightJustified(4, '0');
        QString formatted = padded.left(2) + ":" + padded.right(2);
        emit durationSet(formatted);
        this->hide();
        if (parentWidget()) parentWidget()->show();
    });

}

DurationInputScreen::~DurationInputScreen()
{
    delete ui;
}

void DurationInputScreen::digitClicked(const QString &digit)
{
    if (rawInput.length() < 3) {
        rawInput += digit;
        updateDisplay();
        updateDigitButtonStates();
    }
}

void DurationInputScreen::updateDisplay()
{
    QString padded = rawInput.rightJustified(4, '0');
    QString hours = padded.left(2);
    QString minutes = padded.right(2);
    ui->labelDurationValue->setText(hours + ":" + minutes);
}

void DurationInputScreen::updateDigitButtonStates()
{
    bool hasInput = !rawInput.isEmpty();
    ui->btn0->setEnabled(hasInput);
    ui->btn9->setEnabled(hasInput);
    // Disable 6–9 if only 1 digit is entered
    bool disableHighMinutes = (rawInput.length() == 1);
    ui->btn6->setEnabled(!disableHighMinutes);
    ui->btn7->setEnabled(!disableHighMinutes);
    ui->btn8->setEnabled(!disableHighMinutes);
    ui->btn9->setEnabled(hasInput && !disableHighMinutes);  // special combo
}
