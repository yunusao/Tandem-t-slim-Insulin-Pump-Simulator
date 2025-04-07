#include "createeditprofile.h"
#include "ui_createeditprofile.h"
#include "mainwindow.h"
#include "homescreen.h"
/**
 * @brief CreateEditProfile::CreateEditProfile
 * @param parent
 * @param editProfileId
 *
 * This is the constructor for the profile form. It takes a profileId as the parameter. If the user is not created we set it
 * to -1 to show that it is a new profile. The database automatically updates the id values onces it stored as thats the primary
 * key (check main.cpp for db setup and implementation)
 */

CreateEditProfile::CreateEditProfile(QWidget *parent, int editProfileId, HomeScreen *home) :
    QWidget(parent),
    ui(new Ui::CreateEditProfile), id(editProfileId), homeScreen(home)
{
    ui->setupUi(this);
    qDebug() <<"Create"<< QSqlDatabase::database().databaseName();

    //If already a user, get the id associated with that profile and populate the
    //the input boxes with the values of the fields corressponding to that id
    //The UI allows you to change this value even if its preset
    if (id != -1) {
        qDebug() << id;
        QSqlQuery q;
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
/*
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
*/

/**
 * @brief CreateEditProfile::on_submiButton_clicked
 *
 * Saves a user in the database
 */
void CreateEditProfile::on_submiButton_clicked()
{
    if (ui->nameEdit->text().isEmpty() || ui->basalEdit->text().isEmpty() ||
        ui->carbEdit->text().isEmpty() || ui->corrEdit->text().isEmpty() ||
        ui->targetEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "All fields are required.");
        return;
    }

    QString name = ui->nameEdit->text();
    double newBasal = ui->basalEdit->text().toDouble();
    double newCorr = ui->corrEdit->text().toDouble();
    double newCarb = ui->carbEdit->text().toDouble();
    double newTarget = ui->targetEdit->text().toDouble();

    QSqlQuery q;

    if (id == -1) {
        // Insert new profile
        q.prepare("INSERT INTO profiles (name, basalRate, carbRatio, correctionFactor, glucoseTarget) "
                  "VALUES (:n, :b, :c, :cf, :gt)");
    } else {
        // Fetch previous values for logging changes
        QSqlQuery fetch;
        fetch.prepare("SELECT * FROM profiles WHERE id = :id");
        fetch.bindValue(":id", id);

        if (fetch.exec() && fetch.next()) {
            QString prevName = fetch.value("name").toString();
            double oldBasal = fetch.value("basalRate").toDouble();
            double oldCorr = fetch.value("correctionFactor").toDouble();
            double oldCarb = fetch.value("carbRatio").toDouble();
            double oldTarget = fetch.value("glucoseTarget").toDouble();

            QString profileLabel = "[" + prevName + "]";

            if (!qFuzzyCompare(oldBasal + 1.0, newBasal + 1.0)) {
                homeScreen->logEvent("Profile", "", QString("%1 Basal rate changed from %2 to %3")
                                     .arg(profileLabel).arg(oldBasal).arg(newBasal));
            }
            if (!qFuzzyCompare(oldCorr + 1.0, newCorr + 1.0)) {
                homeScreen->logEvent("Profile", "", QString("%1 Correction factor updated from %2 to %3")
                                     .arg(profileLabel).arg(oldCorr).arg(newCorr));
            }
            if (!qFuzzyCompare(oldCarb + 1.0, newCarb + 1.0)) {
                homeScreen->logEvent("Profile", "", QString("%1 Carb ratio changed from %2 to %3")
                                     .arg(profileLabel).arg(oldCarb).arg(newCarb));
            }
            if (!qFuzzyCompare(oldTarget + 1.0, newTarget + 1.0)) {
                homeScreen->logEvent("Profile", "", QString("%1 Glucose target changed from %2 to %3")
                                     .arg(profileLabel).arg(oldTarget).arg(newTarget));
            }
        }

        // Prepare update query
        q.prepare("UPDATE profiles SET name=:n, basalRate=:b, carbRatio=:c, correctionFactor=:cf, glucoseTarget=:gt "
                  "WHERE id=:id");
        q.bindValue(":id", id);
    }

    // Bind values for insert or update
    q.bindValue(":n", name);
    q.bindValue(":b", newBasal);
    q.bindValue(":c", newCarb);
    q.bindValue(":cf", newCorr);
    q.bindValue(":gt", newTarget);

    if (q.exec()) {
        emit profileSaved();
        if (parentWidget()) {
            parentWidget()->show();
        }
        this->close();
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to save profile.");
    }
}



void CreateEditProfile::on_cancelButton_clicked()
{
    if (parentWidget()) {
        parentWidget()->show();  // return to ProfilePage
    }
    this->close();

}
/*
void CreateEditProfile::on_cancelButton_clicked()
{
    if (QWidget *page = parentWidget()){
        page->show();
    }
    this->close();
}
*/