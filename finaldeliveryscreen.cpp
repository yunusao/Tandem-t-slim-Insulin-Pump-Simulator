#include "finaldeliveryscreen.h"
#include "ui_finaldeliveryscreen.h"

FinalDeliveryScreen::FinalDeliveryScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FinalDeliveryScreen)
{
    ui->setupUi(this);

    confirmDeliveryScreen = new ConfirmDeliveryScreen(this);
    confirmDeliveryScreen->setWindowFlags(Qt::Window);
    confirmDeliveryScreen->hide();

    extendedBolusScreen = new ExtendedBolusScreen(this);
    extendedBolusScreen->setWindowFlags(Qt::Window);
    extendedBolusScreen->hide();

    //Extended Toggle
    connect(ui->toggleExtended, &QCheckBox::toggled, this, &FinalDeliveryScreen::updateTitle);

    //Back Button
    connect(ui->backButton, &QPushButton::clicked, this, [=]() {
        this->hide();  // Hide FinalDeliveryScreen

        if (parentWidget()) {
            parentWidget()->show();  // Show ConfirmBolusScreen
        }
    });
    //Confirm Button
    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        if (ui->toggleExtended->isChecked()) {

            QString food = ui->valueFood->text();
            if (food.endsWith(" u")) food.chop(2);

            extendedBolusScreen->setTotalUnits(food);  // ✅ cleaner and more reliable
            this->hide();
            extendedBolusScreen->show();
        } else {
            confirmDeliveryScreen->setUnits(totalUnits);
            this->hide();
            confirmDeliveryScreen->show();
        }
    });
}

FinalDeliveryScreen::~FinalDeliveryScreen()
{
    delete ui;
}
void FinalDeliveryScreen::setTotalUnits(QString units)
{
    totalUnits = units;   // Save for future use
    updateTitle();        // Call the dynamic update function
}

void FinalDeliveryScreen::updateTitle()
{
    if (ui->toggleExtended->isChecked()) {
        ui->labelTitle->setText("Extend Food Bolus?");
    } else {
        ui->labelTitle->setText("Deliver " + totalUnits + " Bolus?");
    }
}

void FinalDeliveryScreen::setFood(QString food)
{
    valueFood = food;
    ui->labelFood->setText(food + " u");
}
