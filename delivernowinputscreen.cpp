#include "delivernowinputscreen.h"
#include "ui_delivernowinputscreen.h"

DeliverNowInputScreen::DeliverNowInputScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeliverNowInputScreen)
{
    ui->setupUi(this);
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
        percentInput.clear();
        ui->labelPercentValue->setText("0");
    });

    connect(ui->backButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        if (parentWidget()) parentWidget()->show();  // Return to ExtendedBolusScreen
    });

    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        if (!percentInput.isEmpty()) {
            emit percentEntered(percentInput);
            this->hide();
        }
    });


}

DeliverNowInputScreen::~DeliverNowInputScreen()
{
    delete ui;
}

void DeliverNowInputScreen::digitClicked(const QString &digit)
{
    if (percentInput.length() < 3) {  // Prevent more than 3 digits (max 100)
        percentInput += digit;
        ui->labelPercentValue->setText(percentInput);
    }
}

