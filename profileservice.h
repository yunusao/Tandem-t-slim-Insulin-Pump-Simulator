#ifndef PROFILESERVICE_H
#define PROFILESERVICE_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QSqlQuery>
#include <QDebug>

class ProfileService : public QObject
{
    Q_OBJECT

public:
    explicit ProfileService(QObject *parent = nullptr);
    enum User {
        Id,
        Name,
        BasalRate,
        CarbRatio,
        CorrectionFactor,
        GlucoseTarget,
        InsulationDuration
    };
    Q_ENUM(User)

    //setters
    static void setId(int currentId);
    static bool setField(User field, const QVariant &value);
    static void setActiveProfile(int currentId);

    //getters
    static int getId();
    static QVariant getField(User field);

private:
    static int id;
};

#endif // PROFILESERVICE_H
