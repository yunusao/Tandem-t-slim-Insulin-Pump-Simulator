#include "createeditprofile.h"
#include "ui_createeditprofile.h"

CreateEditProfile::CreateEditProfile(QWidget *parent, int editProfileId) :
    QWidget(parent),
    ui(new Ui::CreateEditProfile), id(editProfileId)
{
    ui->setupUi(this);
    qDebug() <<"Create"<< QSqlDatabase::database().databaseName();
    if (id != -1) {
        qDebug() << id;
        QSqlQuery q;;
        q.prepare("SELECT * FROM profiles WHERE id = :id");
        q.bindValue(":id",id);
        q.exec();
        if (q.next()){
            ui->nameEdit->setText(q.value("name").toString());
            ui->basalEdit->setText(q.value("basalRate").toString());
            ui->carbEdit->setText(q.value("carbRatio").toString());
            ui->corrEdit->setText(q.value("correctionFactor").toString());
            ui->targetEdit->setText(q.value("glucoseTarget").toString());
        }
    }
}

CreateEditProfile::~CreateEditProfile()
{
    delete ui;
}

void CreateEditProfile::on_submiButton_clicked()
{
    qDebug() <<"Name: " << ui->nameEdit->text();
    if (ui->nameEdit->text().isEmpty() ||ui->basalEdit->text().isEmpty() ||ui->carbEdit->text().isEmpty() ||
       ui->corrEdit->text().isEmpty() || ui->targetEdit->text().isEmpty()) {
        QMessageBox::warning(this,"Error","All fields are required.");
        return;
    }
    QSqlQuery q(QSqlDatabase::database());
    QString name = ui->nameEdit->text();
    QString basalRate = ui->basalEdit->text();
    QString carbRatio = ui->carbEdit->text();
    QString correctionFactor = ui->corrEdit->text();
    QString glucoseTarget = ui->targetEdit->text();
    if(id == -1) {
        q.prepare("INSERT INTO profiles (name, basalRate, carbRatio, correctionFactor, glucoseTarget) "
                  "VALUES (:n, :b, :c, :cf, :gt)");
    } else {
        q.prepare("UPDATE profiles SET name=:n, basalRate=:b, carbRatio=:c, correctionFactor=:cf, glucoseTarget=:gt "
                  "WHERE id=:id");
        q.bindValue(":id", id);
    }
    q.bindValue(":n", ui->nameEdit->text());
    q.bindValue(":b", ui->basalEdit->text().toDouble());
    q.bindValue(":c", ui->carbEdit->text().toDouble());
    q.bindValue(":cf", ui->corrEdit->text().toDouble());
    q.bindValue(":gt", ui->targetEdit->text().toDouble());
    if (q.exec()){
        this->close();
    }
}


void CreateEditProfile::on_cancelButton_clicked()
{
    if (QWidget *page = parentWidget()){
        page->show();
    }
    this->close();
}
