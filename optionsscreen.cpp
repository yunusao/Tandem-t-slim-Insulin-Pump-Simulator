#include "optionsscreen.h"
#include "ui_optionsscreen.h"
#include "profilepage.h"

OptionsScreen::OptionsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsScreen)
{
    ui->setupUi(this);
}

OptionsScreen::~OptionsScreen()
{
    delete ui;
}

void OptionsScreen::on_personalProfilesButton_clicked()
{
    ProfilePage *page = new ProfilePage();
    page->show();
    this->close();
}

