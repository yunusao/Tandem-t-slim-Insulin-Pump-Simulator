#include "delivernowinputscreen.h"
#include "ui_delivernowinputscreen.h"

/**
 * @brief DeliverNowInputScreen constructor
 * Initializes the screen, sets up UI components and connects signal-slot interactions
 */
DeliverNowInputScreen::DeliverNowInputScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeliverNowInputScreen)
{
    ui->setupUi(this);

    //Connect digit buttons (0-9)
    connect(ui->btn0, &QPushButton::clicked, this, [=]() { digitClicked("0"); });
    connect(ui->btn1, &QPushButton::clicked, this, [=]() { digitClicked("1"); });
    connect(ui->btn2, &QPushButton::clicked, this, [=]() { digitClicked("2"); });
    connect(ui->btn3, &QPushButton::clicked, this, [=]() { digitClicked("3"); });
    connect(ui->btn4, &QPushButton::clicked, this, [=]() { digitClicked("4"); });
    connect(ui->btn5, &QPushButton::clicked, this, [=]() { digitClicked("5"); });
    connect(ui->btn6, &QPushButton::clicked, this, [=]() { digitClicked("6"); });
    connect(ui->btn7, &QPushButton::clicked, this, [=]() { digitClicked("7"); });
    connect(ui->btn8, &QPushButton::clicked, this, [=]() { digitClicked("8"); });
    connect(ui->btn9, &QPushButton::clicked, this, [=]() { digitClicked("9"); });

    //Clear button
    connect(ui->clearButton, &QPushButton::clicked, this, [=]() {
        percentInput.clear();
        ui->labelPercentValue->setText("0");
    });

    //Back button
    connect(ui->backButton, &QPushButton::clicked, this, [=]() {
        this->hide();
        if (parentWidget()) parentWidget()->show();  // Return to ExtendedBolusScreen
    });

    //Confirm
    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        if (!percentInput.isEmpty()) {
            emit percentEntered(percentInput);
            this->hide();
        }
    });


}

/**
 * @brief Destructor
 * Cleans up UI resources
 */
DeliverNowInputScreen::~DeliverNowInputScreen()
{
    delete ui;
}

/**
 * @brief Handle digit button press
 * Appends digit to the percent input string if under 3 characters
 * @param digit The digit clicked ("0"–"9")
 */
void DeliverNowInputScreen::digitClicked(const QString &digit)
{
    if (percentInput.length() < 3) {  // Prevent more than 3 digits (max 100)
        percentInput += digit;
        ui->labelPercentValue->setText(percentInput);
    }
}

