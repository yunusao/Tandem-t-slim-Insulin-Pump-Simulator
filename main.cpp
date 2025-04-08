#include "mainwindow.h"
#include "homescreen.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QApplication>
#include <QObject>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Connect to SQLite database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/insulinTandem.db");
    if (!db.open()) {
        qDebug() << "Failed to open database";
    }

    // Create profiles table
    QSqlQuery query;
    QString createTable = "CREATE TABLE IF NOT EXISTS profiles ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "name TEXT,"
                          "basalRate REAL,"
                          "carbRatio REAL,"
                          "correctionFactor REAL,"
                          "glucoseTarget REAL,"
                          "active INTEGER DEFAULT 0)";
    if (!query.exec(createTable)) {
        qDebug() << "Failed to create profiles table:" << query.lastError().text();
    }

    // Create errorLogs table (used for event logging)
    QSqlQuery query2;
    QString createTable2 = "CREATE TABLE IF NOT EXISTS errorLogs ("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "timestamp TEXT,"
                           "message TEXT)";
    if (!query2.exec(createTable2)) {
        qDebug() << "Failed to create errorLogs table:" << query2.lastError().text();
    }

<<<<<<< HEAD


    QSqlQuery query3;

    QString createAllEventsTable = R"(
        CREATE TABLE IF NOT EXISTS AllEvents (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            timestamp TEXT,
            eventType TEXT,
            amount TEXT,
            notes TEXT
        )
    )";
    if (!query3.exec(createAllEventsTable)) {
        qDebug() << "Failed to create AllEvents table:" << query3.lastError().text();
    }

    qDebug() << "Database path:" << db.databaseName();


    QSqlQuery q(("SELECT id FROM profiles WHERE active = 1 LIMIT 1"));
=======
    // Set active profile if one exists
    QSqlQuery q("SELECT id FROM profiles WHERE active = 1 LIMIT 1");
>>>>>>> iteration-5---jonah
    if (q.exec() && q.next()) {
        int id = q.value(0).toInt();
        ProfileService::setId(id);
        ProfileService::setActiveProfile(id);
        qDebug() << "Active profile loaded with ID:" << id;
    } else {
        qDebug() << "No active profile found.";
    }

    // Apply dark theme stylesheet
    QString darkStyle = R"(
        QWidget {
            background-color: #2b2b2b;
            color: #dcdcdc;
            font-family: "Segoe UI", sans-serif;
        }
        QLabel {
            color: #dcdcdc;
        }
        QLineEdit, QComboBox {
            background-color: #3c3f41;
            color: #dcdcdc;
            border: 1px solid #555555;
            padding: 2px;
        }
        QPushButton {
            background-color: #3c3f41;
            color: #dcdcdc;
            border: 1px solid #555555;
            padding: 5px 10px;
            border-radius: 3px;
        }
        QPushButton:hover {
            background-color: #484a4c;
        }
        QPushButton:pressed {
            background-color: #2d2d2d;
        }
        QProgressBar {
            background-color: #3c3f41;
            border: 1px solid #555555;
            text-align: center;
            color: #dcdcdc;
        }
        QProgressBar::chunk {
            background-color: #0a84ff;
        }
        QLabel#graph {
            background-color: #1e1e1e;
            border: 1px solid #555555;
        }
        QMenuBar {
            background-color: #3c3f41;
            color: #dcdcdc;
        }
        QMenuBar::item {
            background: transparent;
        }
        QMenuBar::item:selected {
            background: #484a4c;
        }
        QMenu {
            background-color: #3c3f41;
            border: 1px solid #555555;
            color: #dcdcdc;
        }
        QMenu::item:selected {
            background-color: #484a4c;
        }
    )";
    a.setStyleSheet(darkStyle);

    // Launch main window
    HomeScreen home;
    home.show();

    return a.exec();
}
