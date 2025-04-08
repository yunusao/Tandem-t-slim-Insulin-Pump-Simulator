#include "optionsscreen.h"
#include "ui_optionsscreen.h"
#include "homescreen.h"
<<<<<<< HEAD
#include <QMessageBox>
=======
#include <QMessageBox>   // Include for message dialog
>>>>>>> iteration-5---jonah

#include "profilepage.h"
OptionsScreen::OptionsScreen(HomeScreen *home, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsScreen),
    homeScreen(home)
{
    ui->setupUi(this);

    profilePage = new ProfilePage(homeScreen, this);

    connect(profilePage, &ProfilePage::newActiveProfile, homeScreen, &HomeScreen::loadActiveUser);
    profilePage->setWindowFlags(Qt::Window);
    profilePage->hide();

    errorLogs = new errorlogpage(this);
    errorLogs->setWindowFlags(Qt::Window);
    errorLogs->hide();

    eventLogPage = new EventLogPage(this);
    eventLogPage->setWindowFlags(Qt::Window);
    eventLogPage->hide();
}

OptionsScreen::~OptionsScreen()
{
    delete ui;
}

void OptionsScreen::on_personalProfilesButton_clicked()
{
    this->hide();
    profilePage->show();
}

void OptionsScreen::on_pushButton_clicked()
{
    this->hide();
    errorLogs->loadErrors();
    errorLogs->show();
}

<<<<<<< HEAD
void OptionsScreen::on_eventLogButton_clicked()
{
    this->hide();
    eventLogPage->loadEvents();
    eventLogPage->show();
}

void OptionsScreen::on_toggleInsulinButton_clicked()
{
    if (homeScreen->isBasalActive()) {
        homeScreen->suspendBasal(true, "Basal insulin delivery manually suspended.");
    } else {
        homeScreen->resumeBasal(true, "Basal insulin delivery manually resumed.");
    }
    updateToggleInsulinLabel();
}

void OptionsScreen::updateToggleInsulinLabel()
{
    if (homeScreen->isBasalActive()) {
        ui->toggleInsulinButton->setText("Suspend Insulin");
    } else {
        ui->toggleInsulinButton->setText("Resume Insulin");
    }
}

=======
void OptionsScreen::updateBasalButtonLabel() {
    // Set button text based on current basal status
    if (homeScreen->isBasalActive()) {
        ui->suspendResumeButton->setText("Suspend Basal");
    } else {
        ui->suspendResumeButton->setText("Resume Basal");
    }
}

void OptionsScreen::on_suspendResumeButton_clicked()
{
    if (homeScreen->isBasalActive()) {
        // Suspend basal insulin delivery
        homeScreen->suspendBasal();  // sets basalActive false and logs event
        ui->suspendResumeButton->setText("Resume Basal");
        QMessageBox::information(this, "Basal Suspended",
                                 "Basal insulin delivery has been suspended.");
    } else {
        // Resume basal insulin delivery
        homeScreen->resumeBasal();   // sets basalActive true and logs event
        ui->suspendResumeButton->setText("Suspend Basal");
        QMessageBox::information(this, "Basal Resumed",
                                 "Basal insulin delivery has been resumed.");
    }
}

// File: optionsscreen.cpp
void OptionsScreen::on_eventLogButton_clicked()
{
    this->hide();
    // Refresh and show the event log page
    errorLogs->loadErrors();
    errorLogs->show();
}
>>>>>>> iteration-5---jonah
