#include "extendedbolusscreen.h"
#include "ui_extendedbolusscreen.h"

/**
 * @brief ExtendedBolusScreen constructor
 * Initializes all child screens and connects button interactions.
 * @param parent Pointer to parent widget (typically FinalDeliveryScreen)
 */
ExtendedBolusScreen::ExtendedBolusScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtendedBolusScreen)
{
    ui->setupUi(this);

    // Initialize Deliver Now input screen
    nowInputScreen = new DeliverNowInputScreen(this);
    nowInputScreen->setWindowFlags(Qt::Window);
    nowInputScreen->hide();

    // Initialize Duration input screen
    durationScreen = new DurationInputScreen(this);
    durationScreen->setWindowFlags(Qt::Window);
    durationScreen->hide();

    // Initialize Confirm Extended Bolus screen
    confirmExtendedBolusScreen = new ConfirmExtendedBolusScreen(this);
    confirmExtendedBolusScreen->setWindowFlags(Qt::Window);
    confirmExtendedBolusScreen->hide();

    //Back button
    connect(ui->backButton, &QPushButton::clicked, this, [=]() {
        this->hide();  // Hide this screen

        if (parentWidget()) {
            parentWidget()->show();  // Show FinalDeliveryScreen
        }
    });

    //Confirm button
    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {

        // Set summary values
        confirmExtendedBolusScreen->setDeliverNow(ui->deliverNowButton->text());     // e.g. "60%"
        confirmExtendedBolusScreen->setDeliverLater(ui->deliverLaterButton->text()); // e.g. "40%"
        confirmExtendedBolusScreen->setDuration(ui->durationButton->text());         // e.g. "1:30"
        confirmExtendedBolusScreen->setTotalUnits(ui->labelTotalUnits->text());

        this->hide();
        confirmExtendedBolusScreen->show();
    });


    //Deliver now button
    connect(ui->deliverNowButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        nowInputScreen->show();
    });

    //Duration button
    connect(ui->durationButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        durationScreen->show();
    });

    //Duration screen update
    connect(durationScreen, &DurationInputScreen::durationSet, this, [=](QString duration) {
        ui->durationButton->setText(duration + " hrs");  // Update the 2hr button text
        this->show();
    });

    //Screen update
    connect(nowInputScreen, &DeliverNowInputScreen::percentEntered, this, [=](QString value){
        ui->deliverNowButton->setText(value + "%");


        bool ok;
        float percent = value.toFloat(&ok);
        if (ok) {
            float remaining = 100.0 - percent;
            ui->deliverLaterButton->setText(QString::number(remaining) + "%");
        }

        this->show();
    });
}

/**
 * @brief Destructor
 */
ExtendedBolusScreen::~ExtendedBolusScreen()
{
    delete ui;
}

/**
 * @brief Sets the total insulin dose for this screen
 * @param units Formatted value like "3.50"
 */
void ExtendedBolusScreen::setTotalUnits(QString units)
{
    ui->labelTotalUnits->setText(units);
}
