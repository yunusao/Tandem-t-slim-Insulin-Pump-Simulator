#include "profilepage.h"
#include "ui_profilepage.h"
#include "createeditprofile.h"

ProfilePage::ProfilePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfilePage)
{
    ui->setupUi(this);
}

ProfilePage::~ProfilePage()
{
    delete ui;
}

void ProfilePage::loadProfiles() {
    ui->profilesTable->setRowCount(0);
    QSqlQuery q("SELECT * FROM profiles");
    int row = 0;;
    while(q.next()){
      int id = q.value("id").toInt();
      ui->profilesTable->insertRow(row);
      ui->profilesTable->setItem(row,0, new QTableWidgetItem(q.value("name").toString()));
      ui->profilesTable->setItem(row,0, new QTableWidgetItem(q.value("basalRate").toString()));
      ui->profilesTable->setItem(row,0, new QTableWidgetItem(q.value("carbRatio").toString()));
      ui->profilesTable->setItem(row,0, new QTableWidgetItem(q.value("correctionFactor").toString()));
      ui->profilesTable->setItem(row,0, new QTableWidgetItem(q.value("glucoseTarget").toString()));
      QPushButton *editButton = new QPushButton("Edit");
      QPushButton *deleteButton = new QPushButton("Delete");
      ui->profilesTable->setCellWidget(row,5,editButton);
      ui->profilesTable->setCellWidget(row,5,deleteButton);
      connect(editButton, &QPushButton::clicked,[=](){
          CreateEditProfile *editProfile = new CreateEditProfile((nullptr,id));
      })


    }


}

void ProfilePage::on_createProfileButton_clicked()
{
    CreateEditProfile *createProfile = new CreateEditProfile(nullptr, -1);


}

