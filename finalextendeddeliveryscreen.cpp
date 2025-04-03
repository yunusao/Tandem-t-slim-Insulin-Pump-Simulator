#include "finalextendeddeliveryscreen.h"
#include "ui_finalextendeddeliveryscreen.h"

FinalExtendedDeliveryScreen::FinalExtendedDeliveryScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FinalExtendedDeliveryScreen)
{
    ui->setupUi(this);

    extendedBolusInitiatedScreen = new ExtendedBolusInitiatedScreen(this);
    extendedBolusInitiatedScreen->setWindowFlags(Qt::Window);
    extendedBolusInitiatedScreen->hide();

    connect(ui->cancelButton, &QPushButton::clicked, this, [=]() {
        this->hide();  // Hide this screen

        if (parentWidget()) {
            parentWidget()->show();  // Go back to ConfirmExtendedBolusScreen
        }
    });

    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        QString now = ui->labelNowCorrection->text();     // Should be "2.382 u"
        QString later = ui->labelLater->text(); // Should be "1.268 u"

        // Trim trailing " u"
        now.chop(2);
        later.chop(2);

        extendedBolusInitiatedScreen->showWithValues(now, later);
        this->hide();
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
