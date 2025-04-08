#include <QMessageBox>
#include <QInputDialog>
#include <QtMath>
#include <QRandomGenerator>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlError>
#include <algorithm>
#include "homescreen.h"
#include "ui_homescreen.h"
#include "mainwindow.h"

// Helper function to log errors
void HomeScreen::logError(const QString &message)
{
    // Log error to database
    QSqlQuery query;
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    query.prepare("INSERT INTO errorLogs (timestamp, message) VALUES (:timestamp, :message)");
    query.bindValue(":timestamp", timestamp);
    query.bindValue(":message", message);
    if (!query.exec()){
        qDebug() << "Failed to log error to database:" << query.lastError().text();
    }
    emit errorSaved();

    // Also log to file
    QFile file("ErrorLogs.txt");
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << timestamp << " - " << message << "\n";
        file.close();
    }
}

// deliverBolus: if durationMs == 0, deliver immediately; otherwise, schedule an extended delivery.
void HomeScreen::deliverBolus(double units, int durationMs)
{
    if (durationMs <= 0) {
        if (units > insulinRemainingUnits)
            units = insulinRemainingUnits;
        insulinRemainingUnits -= units;
        insulinOnBoard += units;
        ui->insulinRemainingBar->setValue(insulinRemainingUnits);
        ui->insulinRemaining->setText(QString::number(insulinRemainingUnits) + "U");
        ui->label_2->setText(QString::number(insulinOnBoard, 'f', 1) + " u");
        logError(QString("Immediate bolus: %1 U delivered.").arg(units, 0, 'f', 1));
    } else {
        BolusDelivery bolus;
        bolus.totalUnits = units;
        bolus.remainingUnits = units;
        bolus.durationMs = durationMs;
        bolus.startTime = QDateTime::currentDateTime();
        bolus.rate = units / static_cast<double>(durationMs); // units per ms
        activeBoluses.append(bolus);
        logError(QString("Extended bolus: %1 U over %2 ms scheduled.").arg(units, 0, 'f', 1).arg(durationMs));
    }
}

HomeScreen::HomeScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomeScreen)
    , timer(new QTimer(this))
    , graphTimer(new QTimer(this))
    , batteryLevel(100)
    , chargingMode(false)
    , insulinRemainingUnits(300)
    , insulinOnBoard(0.0)
    , cgmTimeTick(0)
    , poweredOn(false)      // Device starts powered off
    , batteryCounter(0)
    , basalActive(true)
{
    ui->setupUi(this);
    ui->powerOffOverlay->show(); // Show overlay when off

    loadActiveUser();

    // Set progress bar ranges.
    ui->batteryBar->setRange(0, 100);
    ui->insulinRemainingBar->setRange(0, 300);

    bolusScreen = new BolusScreen(this);
    optionsScreen = new OptionsScreen(this, this);

    // Hide secondary screens.
    bolusScreen->hide();
    optionsScreen->hide();

    // Connect screen navigation buttons.
    connect(ui->bolusButton, &QPushButton::clicked, this, &HomeScreen::showBolusScreen);
    connect(ui->optionsButton, &QPushButton::clicked, this, &HomeScreen::showOptionsScreen);
    connect(bolusScreen->findChild<QPushButton*>("homeButton"), &QPushButton::clicked, this, &HomeScreen::returnHome);
    connect(optionsScreen->findChild<QPushButton*>("homeButton"), &QPushButton::clicked, this, &HomeScreen::returnHome);

    // Connect power buttons.
    connect(ui->powerButton_2, &QPushButton::pressed, this, &HomeScreen::powerPressed);
    connect(ui->powerButton_2, &QPushButton::released, this, &HomeScreen::powerReleased);
    connect(ui->powerButton_3, &QPushButton::clicked, this, &HomeScreen::powerOff);

    // Connect the Disconnect button.
    connect(ui->Disconnect, &QPushButton::clicked, this, &HomeScreen::disconnectCGM);

    // Set timer intervals.
    timer->setInterval(500);
    connect(timer, &QTimer::timeout, this, &HomeScreen::updateTime);

    graphTimer->setInterval(100);
    connect(graphTimer, &QTimer::timeout, this, &HomeScreen::updateGraph);

    // Initialize insulin gauge.
    ui->insulinRemainingBar->setValue(insulinRemainingUnits);

    // Initialize lastGraphY to the vertical center of the graph.
    lastGraphY = ui->graph->height() / 2;

    // Initialize simulation variables.
    baseline = 5.0;
    amplitude = 1.0;

    // Connect charging and refill buttons.
    connect(ui->chargingButton, &QPushButton::clicked, this, &HomeScreen::toggleChargingMode);
    connect(ui->refillButton, &QPushButton::clicked, this, &HomeScreen::refillInsulin);
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::updateTime()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    ui->labelTime->setText(time.toString("hh:mm AP"));
    ui->labelDate->setText(date.toString("dd MMM"));

    if (poweredOn) {
        int elapsedMs = powerOnTime.msecsTo(QDateTime::currentDateTime());
        QTime elapsed = QTime::fromMSecsSinceStartOfDay(elapsedMs);
        ui->timeWindow->setText(elapsed.toString("h:mm:ss"));
    } else {
        ui->timeWindow->setText("0:00:00");
    }

    if (poweredOn) {
        batteryCounter++;
        if (batteryCounter % 4 == 0) {
            if (!chargingMode)
                batteryLevel = std::max(0, batteryLevel - 1);
            else
                batteryLevel = std::min(100, batteryLevel + 1);
        }
        ui->batteryBar->setValue(batteryLevel);
        ui->batteryLabel->setText(QString::number(batteryLevel) + "%");

        // Process active extended bolus deliveries.
        double dt = 500.0; // ms per tick
        for (int i = activeBoluses.size() - 1; i >= 0; i--) {
            BolusDelivery &bolus = activeBoluses[i];
            double delivered = bolus.rate * dt;
            if (delivered > bolus.remainingUnits)
                delivered = bolus.remainingUnits;
            bolus.remainingUnits -= delivered;
            insulinOnBoard += delivered;
            insulinRemainingUnits -= delivered;
            if (insulinRemainingUnits < 0)
                insulinRemainingUnits = 0;
            ui->insulinRemainingBar->setValue(insulinRemainingUnits);
            ui->insulinRemaining->setText(QString::number(insulinRemainingUnits) + "U");
            ui->label_2->setText(QString::number(insulinOnBoard, 'f', 1) + " u");
            if (bolus.remainingUnits <= 0)
                activeBoluses.removeAt(i);
        }

        if (insulinOnBoard > 0) {
            insulinOnBoard = std::max(0.0, insulinOnBoard - 0.125);
            ui->label_2->setText(QString::number(insulinOnBoard, 'f', 1) + " u");

            static bool durationLogged = false;
            if (insulinOnBoard <= 0.0 && !durationLogged) {
                logEvent("Duration", "", "Insulin on board has cleared (duration complete)");
                durationLogged = true;
            }
            if (insulinOnBoard > 0.0) {
                durationLogged = false;
            }
        }

        static bool batteryLowAlertShown = false;
        if (batteryLevel <= 20 && batteryLevel > 0) {
            if (!batteryLowAlertShown) {
                QMetaObject::invokeMethod(this, [this](){
                    QMessageBox::warning(this, "Low Battery", "Battery is low. Please charge the device.");
                }, Qt::QueuedConnection);
                logError("Low Battery: Battery level at " + QString::number(batteryLevel) + "%. Please charge the device.");
                logEvent("Battery Low", QString::number(batteryLevel), "Battery is low");

                batteryLowAlertShown = true;
            }
        } else {
            batteryLowAlertShown = false;
        }
        if (batteryLevel == 0) {
            QMetaObject::invokeMethod(this, [this](){
                QMessageBox::warning(this, "Battery Depleted", "Battery depleted. Device powering off.");
            });
            logError("Battery Depleted: Battery level reached 0%. Device powering off. To continue pumping, please charge. Contact support at 613-807-9580");
            logEvent("Battery Depleted", "0", "Device powered off due to empty battery");
            }, Qt::QueuedConnection);
            logError("Battery Depleted: Battery level reached 0%. Device powering off.");
            powerOff();
        }

        static bool insulinLowAlertShown = false;
        if (insulinRemainingUnits <= 60) {
            if (!insulinLowAlertShown) {
                QMetaObject::invokeMethod(this, [this](){
                    QMessageBox::warning(this, "Low Insulin", "Insulin cartridge is low. Please refill your insulin cartridge.");
                }, Qt::QueuedConnection);

                logError("Low Insulin: Insulin remaining at " + QString::number(insulinRemainingUnits) + "U. Please refill the cartridge.");

                logEvent("Low Insulin", QString::number(insulinRemainingUnits), "Insulin cartridge is low");

                insulinLowAlertShown = true;
            }
        } else {
            insulinLowAlertShown = false;
        }
    } else {
        if (chargingMode) {
            batteryCounter++;
            if (batteryCounter % 4 == 0)
                batteryLevel = std::min(100, batteryLevel + 1);
            ui->batteryBar->setValue(batteryLevel);
            ui->batteryLabel->setText(QString::number(batteryLevel) + "%");
        }
    }
}

void HomeScreen::updateGraph()
{
    if (poweredOn) {
        if (cgmPixmap.isNull()) {
            QSize size = ui->graph->size();
            cgmPixmap = QPixmap(size);
            cgmPixmap.fill(QColor("#1e1e1e"));
        }
        QPixmap scrolled = cgmPixmap.copy(1, 0, cgmPixmap.width() - 1, cgmPixmap.height());
        cgmPixmap.fill(QColor("#1e1e1e"));
        QPainter painter(&cgmPixmap);
        painter.drawPixmap(0, 0, scrolled);

        static bool baselineGoingUp = true;
        static bool amplitudeGoingUp = true;
        double baselineStep = 0.005;
        double amplitudeStep = 0.005;

        if (baselineGoingUp)
            baseline += baselineStep;
        else
            baseline -= baselineStep;
        if (baseline < 5.0) { baseline = 5.0; baselineGoingUp = true; }
        if (baseline > 8.0) { baseline = 8.0; baselineGoingUp = false; }

        if (amplitudeGoingUp)
            amplitude += amplitudeStep;
        else
            amplitude -= amplitudeStep;
        if (amplitude < 0.5) { amplitude = 0.5; amplitudeGoingUp = true; }
        if (amplitude > 1.0) { amplitude = 1.0; amplitudeGoingUp = false; }

        double t = cgmTimeTick / 10.0;
        double fastSine = std::sin(t);
        double newValue = baseline + fastSine * amplitude;
        if (newValue < 3.9) newValue = 3.9;
        if (newValue > 10.0) newValue = 10.0;

        ui->currentBldGlu->setText(QString::number(newValue, 'f', 1));

        int graphHeight = cgmPixmap.height();
        int yPos = graphHeight - static_cast<int>(((newValue - 3.9) / (10.0 - 3.9)) * graphHeight);

        int noise = QRandomGenerator::global()->bounded(5u) - 2;
        yPos += noise;
        if (yPos < 0) yPos = 0;
        if (yPos >= graphHeight) yPos = graphHeight - 1;

        painter.setPen(Qt::white);
        painter.drawLine(cgmPixmap.width() - 2, lastGraphY, cgmPixmap.width() - 1, yPos);
        painter.end();
        ui->graph->setPixmap(cgmPixmap);

        lastGraphY = yPos;
        cgmTimeTick++;


        static bool autoSuspendAlertShown = false;

        if (newValue < 3.9 && basalActive) {
            suspendBasal(true, "Basal insulin delivery suspended automatically (low CGM < 3.9 mmol/L)");
            if (!autoSuspendAlertShown) {
                QMetaObject::invokeMethod(this, [this]() {
                    QMessageBox::warning(this, "Auto Suspend",
                        "Glucose fell below 3.9 mmol/L.\nBasal insulin delivery has been SUSPENDED automatically.");
                }, Qt::QueuedConnection);
                autoSuspendAlertShown = true;
            }
        }
        else if (newValue >= 4.0 && !basalActive) {
            resumeBasal(true, "Basal insulin delivery resumed automatically (CGM stabilized >= 4.0 mmol/L)");
            autoSuspendAlertShown = false;
        }

    }
}

void HomeScreen::powerPressed()
{
    pressStartTime = QDateTime::currentDateTime();
}

void HomeScreen::powerReleased()
{
    int duration = pressStartTime.msecsTo(QDateTime::currentDateTime());
    if (!poweredOn) {
        if (duration >= 3000) {
            poweredOn = true;
            batteryCounter = 0;
            powerOnTime = QDateTime::currentDateTime();
            ui->powerOffOverlay->hide();
            timer->start();
            graphTimer->start();
        } else {
            QMessageBox::information(this, "Power", "Hold the button to power on.");
        }
    }
}

void HomeScreen::powerOff()
{
    poweredOn = false;
    ui->powerOffOverlay->show();
    graphTimer->stop();
}

void HomeScreen::showBolusScreen()
{
    this->hide();
    bolusScreen->setWindowFlags(Qt::Window);
    bolusScreen->show();
    logEvent("Power", "", "Device powered off manually");

}

void HomeScreen::showOptionsScreen()
{
    this->hide();
    optionsScreen->updateBasalButtonLabel();
    optionsScreen->setWindowFlags(Qt::Window);
    optionsScreen->show();
}

void HomeScreen::returnHome()
{
    bolusScreen->hide();
    optionsScreen->hide();
    this->show();
}

void HomeScreen::toggleChargingMode()
{
    chargingMode = !chargingMode;
    ui->chargingButton->setText(chargingMode ? "Stop Charging" : "Start Charging");
}

void HomeScreen::refillInsulin()
{
    insulinRemainingUnits = 300;
    ui->insulinRemainingBar->setValue(insulinRemainingUnits);
    ui->insulinRemaining->setText("300U");
    logEvent("Refill", "300", "Insulin cartridge refilled");

}

void HomeScreen::manualInsulinInjection(double amount)
{
<<<<<<< HEAD
    // If amount is greater than available, limit it.
    if (amount > insulinRemainingUnits)
        amount = insulinRemainingUnits;
    // Decrease the available insulin.
    insulinRemainingUnits -= static_cast<int>(amount);
    ui->insulinRemainingBar->setValue(insulinRemainingUnits);
    ui->insulinRemaining->setText(QString::number(insulinRemainingUnits) + "U");
    // Increase the insulin on board.
    insulinOnBoard += amount;
    ui->label_2->setText(QString::number(insulinOnBoard, 'f', 1) + " u");

    // logging event
    QString msg = QString("Bolus: Manual insulin injection of %1U delivered").arg(amount, 0, 'f', 1);
    logError(msg);;
    QString durationMsg = QString("Insulin duration: %1 hours estimated for %2U bolus").arg("4").arg(amount, 0, 'f', 1);
    logEvent("Duration", QString::number(amount, 'f', 1), durationMsg);
=======
    deliverBolus(amount, 0);
>>>>>>> iteration-5---jonah
}

void HomeScreen::disconnectCGM()
{
    QMessageBox::warning(this, "CGM Disconnection",
        "CGM disconnection trigger detected. Insulin delivery suspended. Please check your CGM connection and press 'OK' once connected.");
    logError("CGM Disconnection: Insulin delivery suspended. Check CGM connection.");
<<<<<<< HEAD
    logEvent("CGM Disconnected", "0", "CGM disconnection trigger detected");

=======
    suspendBasal();
>>>>>>> iteration-5---jonah
}

bool HomeScreen::isBasalActive() const
{
    return basalActive;
}

void HomeScreen::suspendBasal(bool logEvent, const QString &reason)
{
    if (!basalActive)
        return;
    basalActive = false;
    if (logEvent)
        logError(reason);
}

void HomeScreen::resumeBasal(bool logEvent, const QString &reason)
{
    if (basalActive)
        return;
    basalActive = true;
    if (logEvent)
        logError(reason);
}

void HomeScreen::loadActiveUser()
{
    ui->activeUserTable->clearContents();
    ui->activeUserTable->setColumnCount(5);
    ui->activeUserTable->setRowCount(1);

    if (ProfileService::getId() == -1) {
        ui->activeUserTable->setRowCount(0);
        return;
    }
    ui->activeUserTable->setItem(0, 0, new QTableWidgetItem(ProfileService::getField(ProfileService::Name).toString()));
    ui->activeUserTable->setItem(0, 1, new QTableWidgetItem(QString::number(ProfileService::getField(ProfileService::BasalRate).toDouble())));
    ui->activeUserTable->setItem(0, 2, new QTableWidgetItem(QString::number(ProfileService::getField(ProfileService::CarbRatio).toDouble())));
    ui->activeUserTable->setItem(0, 3, new QTableWidgetItem(QString::number(ProfileService::getField(ProfileService::CorrectionFactor).toDouble())));
    ui->activeUserTable->setItem(0, 4, new QTableWidgetItem(QString::number(ProfileService::getField(ProfileService::GlucoseTarget).toDouble())));
    ui->activeUserTable->resizeColumnToContents(0);
    ui->activeUserTable->resizeColumnToContents(1);
    ui->activeUserTable->resizeColumnToContents(2);
    ui->activeUserTable->resizeColumnToContents(3);
    ui->activeUserTable->resizeColumnToContents(4);
}
<<<<<<< HEAD

void HomeScreen::logEvent(const QString &eventType, const QString &amount, const QString &notes)
{
    QSqlQuery query;
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    query.prepare("INSERT INTO AllEvents (timestamp, eventType, amount, notes) "
                  "VALUES (:timestamp, :eventType, :amount, :notes)");

    query.bindValue(":timestamp", timestamp);
    query.bindValue(":eventType", eventType);
    query.bindValue(":amount", amount);
    query.bindValue(":notes", notes);

    if (!query.exec()) {
        qDebug() << "Failed to insert event into AllEvents:" << query.lastError().text();
    }
}

bool HomeScreen::isBasalActive() const {
    return basalActive;
}

void HomeScreen::suspendBasal(bool logEvent1, const QString &reason) {
    if (!basalActive) return;  // Already suspended
    basalActive = false;


    if (graphTimer->isActive()) {
        graphTimer->stop();
    }

    if (logEvent1) {
        logEvent("Insulin", "0", reason);
    }
}

void HomeScreen::resumeBasal(bool logEvent1, const QString &reason) {
    if (basalActive) return;  // Already active
    basalActive = true;

    // 🟢 Resume graph simulation
    if (!graphTimer->isActive()) {
        graphTimer->start();
    }

    if (logEvent1) {
        logEvent("Insulin", "N/A", reason);
    }
}



=======
>>>>>>> iteration-5---jonah
