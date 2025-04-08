#include "confirmdeliveryscreen.h"
#include "ui_confirmdeliveryscreen.h"

ConfirmDeliveryScreen::ConfirmDeliveryScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmDeliveryScreen)
{
    ui->setupUi(this);

    bolusScreen = new BolusInitiatedScreen(this);
    bolusScreen->setWindowFlags(Qt::Window);
    bolusScreen->hide();

    connect(ui->cancelButton, &QPushButton::clicked, this, [=]() {
        this->hide();  // Hide this screen

        if (parentWidget()) {
            parentWidget()->show();  // Show FinalDeliveryScreen
        }
    });
    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        bolusScreen->showWithUnits(ui->labelTitle->text().split(" ")[1]);  // Extract value like "0.49"
    });

}

ConfirmDeliveryScreen::~ConfirmDeliveryScreen()
{
    delete ui;
}

void ConfirmDeliveryScreen::setUnits(QString units)
{
    ui->labelTitle->setText("Deliver " + units + " Bolus?");
}
