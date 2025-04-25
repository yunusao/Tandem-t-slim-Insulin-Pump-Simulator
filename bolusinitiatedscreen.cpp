#include "bolusinitiatedscreen.h"
#include "ui_bolusinitiatedscreen.h"
#include "homescreen.h"
#include <QDebug>

/**
 * @brief BolusInitiatedScreen::BolusInitiatedScreen
 * Constructor that initializes the screen and sets up the auto-close timer.
 */
BolusInitiatedScreen::BolusInitiatedScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BolusInitiatedScreen)
{
    ui->setupUi(this);

    //Initialize the auto-close timer
    autoCloseTimer = new QTimer(this);

    //Connect timer's timeout signal to auto-close logic
    connect(autoCloseTimer, &QTimer::timeout, this, [=]() {
         autoCloseTimer->stop();    //Stop the timer
         this->hide();              //Hide the screen

         // Attempt to show HomeScreen by climbing the parent hierarchy
         if (parentWidget() && parentWidget()->parentWidget()) {
             parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->show();
         }
     });
}

/**
 * @brief BolusInitiatedScreen::~BolusInitiatedScreen
 * Destructor to clean up the UI
 */
BolusInitiatedScreen::~BolusInitiatedScreen()
{
    delete ui;
}

/**
 * @brief BolusInitiatedScreen::showWithUnits
 * Displays the screen with the given bolus unit value and starts a 3-second auto-close timer.
 *
 * @param units The insulin units delivered (e.g., "0.49")
 */
void BolusInitiatedScreen::showWithUnits(QString units)
{
    ui->labelUnits->setText(units + " u");
    this->show();
    HomeScreen* home = nullptr;
        QWidget* w = this;
        while (w && !home) {
            home = qobject_cast<HomeScreen*>(w);
            w = w->parentWidget();
        }
        if (home) {
            home->deliverBolus(units.toDouble(), 100); // Extended bolus delivery
            qDebug()<<"Does it work";
            qDebug()<<units.toDouble();
        }
    autoCloseTimer->start(3000);  // 3 seconds

}
