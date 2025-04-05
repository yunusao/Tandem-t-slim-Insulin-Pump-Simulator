#include "confirmdeliveryscreen.h"
#include "ui_confirmdeliveryscreen.h"
#include "homescreen.h"
#include <QMessageBox>
#include <QMetaObject>

ConfirmDeliveryScreen::ConfirmDeliveryScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmDeliveryScreen)
{
    ui->setupUi(this);

    bolusScreen = new BolusInitiatedScreen(this);
    bolusScreen->setWindowFlags(Qt::Window);
    bolusScreen->hide();

    connect(ui->cancelButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        if (parentWidget()) {
            parentWidget()->show();
        }
    });
    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        // Extract dose from title text, e.g., "Deliver X u Bolus?"
        QString titleText = ui->labelTitle->text();
        QStringList parts = titleText.split(" ");
        double dose = 0.0;
        if (parts.size() >= 2)
            dose = parts.at(1).toDouble();

        // Find HomeScreen in the parent chain.
        HomeScreen* home = nullptr;
        QWidget* w = this;
        while (w && !home) {
            home = qobject_cast<HomeScreen*>(w);
            w = w->parentWidget();
        }
        if (home) {
            home->deliverBolus(dose, 0); // Immediate bolus
        }
        this->hide();
        bolusScreen->showWithUnits(QString::number(dose, 'f', 1));
    });
}

ConfirmDeliveryScreen::~ConfirmDeliveryScreen()
{
    delete ui;
}

void ConfirmDeliveryScreen::setUnits(QString units)
{
    ui->labelTitle->setText("Deliver " + units + " u Bolus?");
}
