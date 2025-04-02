#include "finalextendeddeliveryscreen.h"
#include "ui_finalextendeddeliveryscreen.h"

FinalExtendedDeliveryScreen::FinalExtendedDeliveryScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FinalExtendedDeliveryScreen)
{
    ui->setupUi(this);

    connect(ui->cancelButton, &QPushButton::clicked, this, [=]() {
        this->hide();  // Hide this screen

        if (parentWidget()) {
            parentWidget()->show();  // Go back to ConfirmExtendedBolusScreen
        }
    });
}

FinalExtendedDeliveryScreen::~FinalExtendedDeliveryScreen()
{
    delete ui;
}

void FinalExtendedDeliveryScreen::setTitle(QString t) {
    ui->labelTitle->setText(t);
}

void FinalExtendedDeliveryScreen::setNowCorrection(QString val) {
    ui->labelNowCorrection->setText(val);
}

void FinalExtendedDeliveryScreen::setLater(QString val) {
    ui->labelLater->setText(val);
}

void FinalExtendedDeliveryScreen::setDuration(QString val) {
    ui->labelDuration->setText(val);
}
