#include "extendedbolusinitiatedscreen.h"
#include "ui_extendedbolusinitiatedscreen.h"

/**
 * @brief ExtendedBolusInitiatedScreen constructor
 * Initializes the UI and sets up the auto-close timer for this screen.
 * @param parent Pointer to the parent QWidget
 */
ExtendedBolusInitiatedScreen::ExtendedBolusInitiatedScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtendedBolusInitiatedScreen)
{
    ui->setupUi(this);
    autoCloseTimer = new QTimer(this);

    //Auto-close timer
    connect(autoCloseTimer, &QTimer::timeout, this, [=]() {
        autoCloseTimer->stop();
        this->hide();

        // Show HomeScreen (assuming 5 parents deep)
        if (parentWidget() && parentWidget()->parentWidget()) {
            parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->show();
        }
    });
}

/**
 * @brief Destructor for ExtendedBolusInitiatedScreen
 * Frees memory used by the UI
 */
ExtendedBolusInitiatedScreen::~ExtendedBolusInitiatedScreen()
{
    delete ui;
}

/**
 * @brief Displays the confirmation screen with insulin amounts
 * Shows the screen and sets a label like "0.5 u Now + 0.3 u Later"
 * Automatically hides after 3 seconds.
 * @param now Amount of insulin to deliver immediately
 * @param later Amount of insulin to deliver later
 */
void ExtendedBolusInitiatedScreen::showWithValues(QString now, QString later)
{
    ui->labelUnits->setText(now + " u Now + " + later + " u Later");
    this->show();
    autoCloseTimer->start(3000);  // Show for 3 seconds
}
