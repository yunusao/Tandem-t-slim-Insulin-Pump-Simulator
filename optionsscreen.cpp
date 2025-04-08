#include "optionsscreen.h"
#include "ui_optionsscreen.h"
#include "homescreen.h"
#include "eventlogpage.h"
#include <QMessageBox>

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