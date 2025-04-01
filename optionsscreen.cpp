#include "optionsscreen.h"
#include "ui_optionsscreen.h"
#include "profilepage.h"

OptionsScreen::OptionsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsScreen)
{
    ui->setupUi(this);
    profilePage = new ProfilePage(this);
    profilePage->setWindowFlags(Qt::Window);
    profilePage->hide();
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
