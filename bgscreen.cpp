#include "bgscreen.h"
#include "ui_bgscreen.h"

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
    // repeat for btn2–btn9

    connect(ui->btnClear, &QPushButton::clicked, this, &bgscreen::clearInput);
    connect(ui->btnPlusMinus, &QPushButton::clicked, this, &bgscreen::toggleSign);

    // Confirm
    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        emit bgEntered(bgInput);
        this->hide();
        parentWidget()->show();  // Show BolusScreen
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

void bgscreen::toggleSign()
{
    if (bgInput.startsWith("-")) {
        bgInput.remove(0, 1);
    } else if (bgInput != "0") {
        bgInput = "-" + bgInput;
    }
    ui->labelBgValue->setText(bgInput);
}
