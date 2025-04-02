#include "confirmextendedbolusscreen.h"
#include "ui_confirmextendedbolusscreen.h"

ConfirmExtendedBolusScreen::ConfirmExtendedBolusScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmExtendedBolusScreen)
{
    ui->setupUi(this);

    finalExtendedDeliveryScreen = new FinalExtendedDeliveryScreen(this);
    finalExtendedDeliveryScreen->setWindowFlags(Qt::Window);
    finalExtendedDeliveryScreen->hide();

    connect(ui->cancelButton, &QPushButton::clicked, this, [=]() {
        this->hide();  // Hide this screen

        if (parentWidget()) {
            parentWidget()->show();  // Show ExtendedBolusScreen again
        }
    });

    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        bool ok;
        double units = totalUnits.toDouble(&ok);

        QString nowStr = nowPercent;
        QString laterStr = laterPercent;

        nowStr.chop(1);   // remove "%"
        laterStr.chop(1); // remove "%"

        double nowVal = nowStr.toDouble() / 100.0;
        double laterVal = laterStr.toDouble() / 100.0;

        QString nowCorrection = ok ? QString::number(units * nowVal, 'f', 3) + " u" : "0.000 u";
        QString later = ok ? QString::number(units * laterVal, 'f', 3) + " u" : "0.000 u";

        finalExtendedDeliveryScreen->setTitle("Deliver " + totalUnits + " u Bolus?");
        finalExtendedDeliveryScreen->setNowCorrection(nowCorrection);
        finalExtendedDeliveryScreen->setLater(later);
        finalExtendedDeliveryScreen->setDuration(duration);

        this->hide();
        finalExtendedDeliveryScreen->show();
    });



}

ConfirmExtendedBolusScreen::~ConfirmExtendedBolusScreen()
{
    delete ui;
}

void ConfirmExtendedBolusScreen::setDeliverNow(QString value) {
    ui->labelDeliverNow->setText(value);
    nowPercent = value;
}

void ConfirmExtendedBolusScreen::setDeliverLater(QString value) {
    ui->labelDeliverLater->setText(value);
    laterPercent = value;
}

void ConfirmExtendedBolusScreen::setDuration(QString value) {
    ui->labelDuration->setText(value);
    duration = value;
}

void ConfirmExtendedBolusScreen::setTotalUnits(QString value) {
    totalUnits = value;
}


