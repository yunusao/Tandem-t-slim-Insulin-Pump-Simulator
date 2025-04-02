#include "extendedbolusscreen.h"
#include "ui_extendedbolusscreen.h"

ExtendedBolusScreen::ExtendedBolusScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtendedBolusScreen)
{
    ui->setupUi(this);
    nowInputScreen = new DeliverNowInputScreen(this);
    nowInputScreen->setWindowFlags(Qt::Window);
    nowInputScreen->hide();

    durationScreen = new DurationInputScreen(this);
    durationScreen->setWindowFlags(Qt::Window);
    durationScreen->hide();

    confirmExtendedBolusScreen = new ConfirmExtendedBolusScreen(this);
    confirmExtendedBolusScreen->setWindowFlags(Qt::Window);
    confirmExtendedBolusScreen->hide();


    connect(ui->backButton, &QPushButton::clicked, this, [=]() {
        this->hide();  // Hide this screen

        if (parentWidget()) {
            parentWidget()->show();  // Show FinalDeliveryScreen
        }
    });

    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        // Set summary values
        confirmExtendedBolusScreen->setDeliverNow(ui->deliverNowButton->text());     // e.g. "60%"
        confirmExtendedBolusScreen->setDeliverLater(ui->deliverLaterButton->text()); // e.g. "40%"
        confirmExtendedBolusScreen->setDuration(ui->durationButton->text());         // e.g. "1:30"
        confirmExtendedBolusScreen->setTotalUnits(ui->labelTotalUnits->text());

        this->hide();
        confirmExtendedBolusScreen->show();
    });


    connect(ui->deliverNowButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        nowInputScreen->show();
    });

    connect(ui->durationButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        durationScreen->show();
    });

    connect(durationScreen, &DurationInputScreen::durationSet, this, [=](QString duration) {
        ui->durationButton->setText(duration + " hrs");  // Update the 2hr button text
        this->show();
    });

    connect(nowInputScreen, &DeliverNowInputScreen::percentEntered, this, [=](QString value){
        ui->deliverNowButton->setText(value + "%");

        // Optionally update "Later" % too
        bool ok;
        float percent = value.toFloat(&ok);
        if (ok) {
            float remaining = 100.0 - percent;
            ui->deliverLaterButton->setText(QString::number(remaining) + "%");
        }

        this->show();
    });
}

ExtendedBolusScreen::~ExtendedBolusScreen()
{
    delete ui;
}

void ExtendedBolusScreen::setTotalUnits(QString units)
{
    ui->labelTotalUnits->setText(units);
}
