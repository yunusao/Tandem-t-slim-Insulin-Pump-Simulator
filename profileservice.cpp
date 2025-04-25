#include "profileservice.h"


int ProfileService::id = 0;
ProfileService::ProfileService(QObject *parent) : QObject(parent)
{
}

void ProfileService::setId(int currentId){
    id = currentId;
}

int ProfileService::getId(){
    return id;
}

void ProfileService::setActiveProfile(int currentId){
    QSqlQuery query;
    if (!query.exec("UPDATE profiles set active = 0")){
        return;
    }
    query.prepare("UPDATE profiles set active = 1 WHERE id = :id");
    query.bindValue(":id", currentId);
    query.exec();
    setId(currentId);
}

bool ProfileService::setField(User field, const QVariant &value)
{
    if (id == -1) {
        return false;
    }
    QString fieldName;
    switch (field) {
        case Id:
            fieldName = "id";

        case Name:
            fieldName = "name";

        case BasalRate :
            fieldName = "basalRate";

        case CarbRatio :
            fieldName = "carbRatio";

        case CorrectionFactor :
            fieldName = "correctionFactor";

        case GlucoseTarget :
            fieldName = "glucoseTarget";

        case InsulationDuration :
            fieldName = "insulationDuration";
    }
    QSqlQuery query;
    query.prepare("UPDATE profiles SET " + fieldName + " = :val WHERE id = :id");
    query.bindValue(":val", value);
    query.bindValue(":id", getId());
    if (!query.exec()) {
        return false;
    }
    return true;
}

QVariant ProfileService::getField(User field){
    if (getId() == -1) {
        return false;
    }
    QString fieldName;
    switch (field) {
        case Id:
            fieldName = "id";
            break;

        case Name:
            fieldName = "name";
            break;

        case BasalRate:
            fieldName = "basalRate";
            break;

        case CarbRatio :
            fieldName = "carbRatio";
            break;

        case CorrectionFactor :
            fieldName = "correctionFactor";
            break;

        case GlucoseTarget :
            fieldName = "glucoseTarget";
            break;

        case InsulationDuration :
            fieldName = "insulationDuration";
            break;
    }
     QSqlQuery query;
     query.prepare("SELECT " + fieldName + " FROM profiles WHERE id = :id");
     query.bindValue(":id", getId());
     query.exec();
     if (query.next()){
         return query.value(0);
     }
}






