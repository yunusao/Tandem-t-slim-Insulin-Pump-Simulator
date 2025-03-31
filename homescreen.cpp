#include <QTimer>
#include <QDateTime>
#include <QMessageBox>
#include "homescreen.h"
#include "ui_homescreen.h"

HomeScreen::HomeScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomeScreen)
    , timer(new QTimer(this))  // Initialize timer
{
    ui->setupUi(this);
    ui->powerOffOverlay->show();

    bolusScreen = new BolusScreen(this);
    optionsScreen = new OptionsScreen(this);

    // Hide them initially
    bolusScreen->hide();
    optionsScreen->hide();

    // Connect buttons to switch
    connect(ui->bolusButton, &QPushButton::clicked, this, &HomeScreen::showBolusScreen);
    connect(ui->optionsButton, &QPushButton::clicked, this, &HomeScreen::showOptionsScreen);

    // Tandem logo returns to home (from inside Bolus/Options)
    connect(bolusScreen->findChild<QPushButton*>("homeButton"), &QPushButton::clicked, this, &HomeScreen::returnHome);
    connect(optionsScreen->findChild<QPushButton*>("homeButton"), &QPushButton::clicked, this, &HomeScreen::returnHome);

    connect(ui->powerButton_2, &QPushButton::pressed, this, &HomeScreen::powerPressed);
    connect(ui->powerButton_2, &QPushButton::released, this, &HomeScreen::powerReleased);

    // Connect the timer's timeout signal to updateTime slot
    connect(timer, &QTimer::timeout, this, &HomeScreen::updateTime);

    // Start the timer to update every 1 second (1000 ms)
    timer->start(1000);

    // Immediately update time and date when screen loads
    updateTime();
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::updateTime()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();

    // Set the time in format like "12:00 AM"
    ui->labelTime->setText(time.toString("hh:mm AP"));

    // Set the date in format like "26 Apr"
    ui->labelDate->setText(date.toString("dd MMM"));
}

void HomeScreen::powerPressed()
{
    pressStartTime = QDateTime::currentDateTime();
}

void HomeScreen::powerReleased()
{
    int duration = pressStartTime.msecsTo(QDateTime::currentDateTime());
    if (duration >= 3000) {
        ui->powerOffOverlay->hide();  // Reveal the Home UI
    } else {
        QMessageBox::information(this, "Power", "Hold the button to power on.");
    }
}

void HomeScreen::showBolusScreen() {
    this->hide();            // hide Home
    //bolusScreen->show();     // show Bolus
    bolusScreen->setWindowFlags(Qt::Window);  // Makes it a standalone window
    bolusScreen->show();

}

void HomeScreen::showOptionsScreen() {
    this->hide();
    //optionsScreen->show();
    optionsScreen->setWindowFlags(Qt::Window);  // Makes it a standalone window
    optionsScreen->show();
}

void HomeScreen::returnHome() {
    bolusScreen->hide();
    optionsScreen->hide();
    this->show();            // Show Home again
}


