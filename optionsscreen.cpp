#include "optionsscreen.h"
#include "ui_optionsscreen.h"
#include "profilepage.h"
#include "homescreen.h"

OptionsScreen::OptionsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsScreen)
{
    ui->setupUi(this);
    profilePage = new ProfilePage(this);
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

