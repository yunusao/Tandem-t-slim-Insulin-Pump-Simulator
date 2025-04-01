#include "createeditprofile.h"
#include "ui_createeditprofile.h"

CreateEditProfile::CreateEditProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateEditProfile)
{
    ui->setupUi(this);
}

CreateEditProfile::~CreateEditProfile()
{
    delete ui;
}
