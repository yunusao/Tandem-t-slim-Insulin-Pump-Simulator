#include "confirmextendedbolusscreen.h"
#include "ui_confirmextendedbolusscreen.h"
#include "homescreen.h"
#include <QMessageBox>
#include <QMetaObject>

ConfirmExtendedBolusScreen::ConfirmExtendedBolusScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmExtendedBolusScreen)
{
    ui->setupUi(this);

    finalExtendedDeliveryScreen = new FinalExtendedDeliveryScreen(this);
    finalExtendedDeliveryScreen->setWindowFlags(Qt::Window);
    finalExtendedDeliveryScreen->hide();

    connect(ui->cancelButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        if (parentWidget()) {
            parentWidget()->show();
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

            // Retrieve total units from label (assumes text like "Deliver X u Bolus?")
                    QString titleText = ui->labelTitle->text();
                    QStringList parts = titleText.split(" ");
                    double dose = 0.0;
                    if (parts.size() >= 2)
                        dose = parts.at(1).toDouble();

                    // Retrieve duration from the UI button text (assumes "X:YY hrs" format)
                    QString durationText = ui->labelDuration->text(); // e.g., "1:30 hrs"
                    durationText = durationText.split(" ").first(); // "1:30"
                    QStringList hm = durationText.split(":");
                    int durationMs = 0;
                    if (hm.size() == 2) {
                        int hours = hm.at(0).toInt();
                        int minutes = hm.at(1).toInt();
                        durationMs = ((hours * 60) + minutes) * 60000;
                    }

                    // Find HomeScreen in the parent chain.
                    HomeScreen* home = nullptr;
                    QWidget* w = this;
                    while (w && !home) {
                        home = qobject_cast<HomeScreen*>(w);
                        w = w->parentWidget();
                    }
                    if (home) {
                        home->deliverBolus(dose, durationMs); // Extended bolus delivery
                    }
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
    //ui->labelTitle->setText("Deliver " + value + " u Bolus?");
    ui->labelTitle->setText("Deliver " + value + " u Bolus?");
    totalUnits = value;
}
