#include "profilepage.h"
#include "ui_profilepage.h"
#include "createeditprofile.h"

ProfilePage::ProfilePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfilePage)
{
    qDebug() <<"Profile"<< QSqlDatabase::database().databaseName();
    ui->setupUi(this);
    loadProfiles();
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
      ui->profilesTable->setItem(row,1, new QTableWidgetItem(q.value("basalRate").toString()));
      ui->profilesTable->setItem(row,2, new QTableWidgetItem(q.value("carbRatio").toString()));
      ui->profilesTable->setItem(row,3, new QTableWidgetItem(q.value("correctionFactor").toString()));
      ui->profilesTable->setItem(row,4, new QTableWidgetItem(q.value("glucoseTarget").toString()));
      QPushButton *editButton = new QPushButton("Edit");
      QPushButton *deleteButton = new QPushButton("Delete");
      ui->profilesTable->setCellWidget(row,5,editButton);
      ui->profilesTable->setCellWidget(row,6,deleteButton);
      //edit button
      connect(editButton, &QPushButton::clicked, [=]() {
          qDebug() << id;

          CreateEditProfile *editProfile = new CreateEditProfile(this, id);
          editProfile->setWindowFlags(Qt::Window);

          connect(editProfile, &CreateEditProfile::profileSaved, this, &ProfilePage::loadProfiles);  // ✅ Add this line

          this->hide();
          editProfile->show();
      });

      connect(deleteButton, &QPushButton::clicked,[=](){
          if(QMessageBox::question(this, "Confirm Delete","Are you sure",
                                   QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
              QSqlQuery del;
              del.prepare("DELETE FROM profiles WHERE id=:id");
              del.bindValue(":id",id);
              del.exec();
              loadProfiles();
          }
      });
      row++;
    }


}

void ProfilePage::on_createProfileButton_clicked()
{
    //CreateEditProfile *createProfile = new CreateEditProfile(nullptr, -1);
    CreateEditProfile *createProfile = new CreateEditProfile(this, -1);
    createProfile->setWindowFlags(Qt::Window);  // ✅ Make it a standalone screen
    this->hide();
    createProfile->show();
    connect(createProfile, &CreateEditProfile::profileSaved, this, &ProfilePage::loadProfiles);  // ✅ refresh on save
    //connect(createProfile,&QWidget::destroyed,this,&ProfilePage::loadProfiles);
}


void ProfilePage::on_backButton_clicked()
{
    this->hide();
    if ( parentWidget()){
        parentWidget()->show();
    }

}

