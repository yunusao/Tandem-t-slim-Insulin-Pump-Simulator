#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QPixmap>
#include <QPainter>
#include <QSqlQuery>
#include <QDebug>
#include <QTableWidget>
#include <QString>

#include "bolusscreen.h"
#include "optionsscreen.h"
#include "profileservice.h"

namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = nullptr);
    ~HomeScreen();
    bool isBasalActive() const;            // Check basal status
    void suspendBasal(bool logEvent = true, const QString &reason = "Basal insulin delivery suspended.");
    void resumeBasal(bool logEvent = true, const QString &reason = "Basal insulin delivery resumed.");


public slots:
    void manualInsulinInjection(double amount);
    void loadActiveUser();

private slots:
    void updateTime();      // Battery & IOB updates (500ms)
    void updateGraph();     // CGM graph updates (100ms)

    void powerPressed();
    void powerReleased();

    void powerOff();        // Slot for powerButton_3

    void showBolusScreen();
    void showOptionsScreen();
    void returnHome();

    void toggleChargingMode();
    void refillInsulin();

    void disconnectCGM();   // Slot for Disconnect button


private:
    void logError(const QString &message);

    Ui::HomeScreen *ui;
    QTimer *timer;       // For battery/IOB updates (500ms)
    QTimer *graphTimer;  // For CGM graph updates (100ms)
    QDateTime pressStartTime;
    QDateTime powerOnTime;  // Time when device was powered on

    BolusScreen *bolusScreen;
    OptionsScreen *optionsScreen;

    int batteryLevel;          // [0, 100]
    bool chargingMode;         // Charging active flag
    int insulinRemainingUnits; // [0, 300]
    double insulinOnBoard;     // Active insulin (u)
    QPixmap cgmPixmap;         // For CGM graph
    int cgmTimeTick;           // Simulation tick for graph

    bool poweredOn;            // True when device is on
    int batteryCounter;        // Counts 500ms ticks for battery updates

    int lastGraphY;            // Y coordinate of the last drawn graph point

    // Variables used in the graph approach.
    double baseline;
    double amplitude;
    bool basalActive;  // Track if basal delivery is active (true) or suspended (false)

signals:
    void errorSaved();
};

#endif // HOMESCREEN_H
