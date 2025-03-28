#include <QTimer>
#include <QDateTime>
#include "homescreen.h"
#include "ui_homescreen.h"

HomeScreen::HomeScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomeScreen)
    , timer(new QTimer(this))  // Initialize timer
{
    ui->setupUi(this);

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
