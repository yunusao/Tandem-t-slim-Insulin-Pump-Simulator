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
}

void ConfirmExtendedBolusScreen::setDeliverLater(QString value) {
    ui->labelDeliverLater->setText(value);
}

void ConfirmExtendedBolusScreen::setDuration(QString value) {
    ui->labelDuration->setText(value + " hrs");
}

void ConfirmExtendedBolusScreen::setTotalUnits(QString value) {
    ui->labelTitle->setText("Deliver " + value + " u Bolus?");
}
