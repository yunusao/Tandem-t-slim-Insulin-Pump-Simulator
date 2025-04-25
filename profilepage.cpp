#include "profilepage.h"
#include "ui_profilepage.h"
#include "createeditprofile.h"
#include "homescreen.h"

ProfilePage::ProfilePage(HomeScreen *home, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfilePage),
    homescreen(home)
{
    qDebug() <<"Profile"<< QSqlDatabase::database().databaseName();
    ui->setupUi(this);
    loadProfiles();
}

ProfilePage::~ProfilePage()
{
    delete ui;
}

/**
 * @brief ProfilePage::loadProfiles
 *
 * Goes through the profiles table  in the db and pulls all of its data for each id.
 * Presets value of the table to whatever is pulleed from db. Id is used to match value
 * to profile.
 *
 */
void ProfilePage::loadProfiles() {
    ui->profilesTable->setRowCount(0);
    QSqlQuery q("SELECT * FROM profiles");
    int row = 0;
    while(q.next()){
      int id = q.value("id").toInt();
      ui->profilesTable->insertRow(row);
      ui->profilesTable->setItem(row,0, new QTableWidgetItem(q.value("name").toString()));
      ui->profilesTable->setItem(row,1, new QTableWidgetItem(q.value("basalRate").toString()));
      ui->profilesTable->setItem(row,2, new QTableWidgetItem(q.value("carbRatio").toString()));
      ui->profilesTable->setItem(row,3, new QTableWidgetItem(q.value("correctionFactor").toString()));
      ui->profilesTable->setItem(row,4, new QTableWidgetItem(q.value("glucoseTarget").toString()));
      ui->profilesTable->setItem(row,5, new QTableWidgetItem(q.value("insulationDuration").toString()));
      QPushButton *editButton = new QPushButton("Edit");
      QPushButton *deleteButton = new QPushButton("Delete");
      ui->profilesTable->setCellWidget(row,6,editButton);
      ui->profilesTable->setCellWidget(row,7,deleteButton);

      //edit button
      connect(editButton, &QPushButton::clicked, [=]() {
          qDebug() << id;

          CreateEditProfile *editProfile = new CreateEditProfile(this, id, homescreen);
          editProfile->setWindowFlags(Qt::Window);
                  connect(editProfile, &CreateEditProfile::profileSaved, this, [=]() {
                  loadProfiles();
                  if (ProfileService::getId() == id) {
                      qDebug() << "Update active";
                      emit newActiveProfile();
                  }
          });
          this->hide();
          editProfile->show();
      });

      //delete button
      connect(deleteButton, &QPushButton::clicked,[=](){
          if(QMessageBox::question(this, "Confirm Delete","Are you sure",
                                   QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
              QSqlQuery del;
              del.prepare("DELETE FROM profiles WHERE id=:id");
              del.bindValue(":id",id);
              del.exec();
              ProfileService::setActiveProfile(0);
              emit newActiveProfile();
              loadProfiles();
          }
      });
     if (q.value("active").toInt() == 1) {
         QLabel *label = new QLabel("Active");
         label->setAlignment(Qt::AlignCenter);
         ui->profilesTable->setCellWidget(row,7,label);
     } else {
        QPushButton *activeButton = new QPushButton("Set Active");
        connect(activeButton,&QPushButton::clicked, [=]() {
            ProfileService::setActiveProfile(id);
            emit newActiveProfile();
            loadProfiles();
        });
        ui->profilesTable->setCellWidget(row,7,activeButton);
     }
    }


}

void ProfilePage::on_createProfileButton_clicked()
{
    //CreateEditProfile *createProfile = new CreateEditProfile(nullptr, -1);
    CreateEditProfile *createProfile = new CreateEditProfile(this, -1, homescreen);

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



