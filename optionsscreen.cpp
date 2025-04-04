#include "optionsscreen.h"
#include "ui_optionsscreen.h"
#include "profilepage.h"
#include "homescreen.h"
#include <QMessageBox>   // Include for message dialog

OptionsScreen::OptionsScreen(HomeScreen *home, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsScreen),
    homeScreen(home)
{
    ui->setupUi(this);
    profilePage = new ProfilePage(this);
    connect(profilePage, &ProfilePage::newActiveProfile, homeScreen, &HomeScreen::loadActiveUser);
    profilePage->setWindowFlags(Qt::Window);
    profilePage->hide();

    errorLogs = new errorlogpage(this);
    errorLogs->setWindowFlags(Qt::Window);
    errorLogs->hide();
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
