// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPluginLoader>
#include <QVariant>

void connectDB()
{
    qInfo() << "Opening Database";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("db4free.net");
    db.setDatabaseName("gkhnmlym");
    db.setUserName("gkhnmlym");
    db.setPassword("gkhnmlym-password");

    if(!db.open())
    {
        qInfo() << "Failed to connect!";
        qInfo() << db.lastError().text();
        return;
    }

    qInfo() << "Connected!";
    db.close();
}

void writeToDatabase(const QString &machineId, double hopperTemp, double cylinderTemp)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("localhost");
    //db.setDatabaseName("your_database_name"); // Change this to your actual database name
    //db.setUserName("your_username"); // Change this to your actual username
    //db.setPassword("your_password"); // Change this to your actual password

    if (!db.open())
    {
        qInfo() << "Could not open connection!";
        qInfo() << db.lastError().text();
        return;
    }

    QSqlQuery query;
    QString insertQuery = "INSERT INTO your_table_name (machineId, hopperTemp, cylinderTemp) "
                          "VALUES (:machineId, :hopperTemp, :cylinderTemp)";

    query.prepare(insertQuery);
    query.bindValue(":machineId", machineId);
    query.bindValue(":hopperTemp", hopperTemp);
    query.bindValue(":cylinderTemp", cylinderTemp);

    if (!query.exec())
    {
        qInfo() << "Error executing insert query!";
        qInfo() << query.lastError().text();
    }
    else
    {
        qInfo() << "Data inserted successfully!";
    }

    db.close();
}

void connectLocalDB()
{
    qInfo() << "Opening the database";
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost"); // 127.0.0.1
    db.setUserName("qt6ca");  //Change the username
    db.setPassword("qt6ca-password"); //Change the password

    if(!db.open())
    {
        qInfo() << "Could not open connection!";
        qInfo() << db.lastError().text();
    }
    else
    {
        qInfo() << "Connected, lets make a query...";
        QSqlQuery query;
        QString cmd = "SELECT name,age FROM voidrealms.users WHERE age > 40;";

        if(!query.exec(cmd))
        {
            qInfo() << db.lastError().text();
            qInfo() << query.lastError().text();
        }
        else
        {
            qInfo() << "Got query results: " << query.size();
            while(query.next())
            {
                QString name = query.value(0).toString();
                int age = query.value(1).toInt();

                qInfo() << " name: " << name << " is " << age;
            }
        }

        db.close();
        qInfo() << "Disconnected";

    }
}

void listDB()
{
    qInfo() << "Inspecting Drivers";

    foreach(QString driver, QSqlDatabase::drivers())
    {
        qInfo()<< driver;

        QSqlDatabase db = QSqlDatabase::addDatabase(driver);
        QSqlDriver *obj = db.driver();

        qInfo() << "Transactions: " << obj->hasFeature(QSqlDriver::DriverFeature::Transactions);
        qInfo() << "QuerySize: " << obj->hasFeature(QSqlDriver::DriverFeature::QuerySize);
        qInfo() << "BLOB: " << obj->hasFeature(QSqlDriver::DriverFeature::BLOB);
        qInfo() << "Unicode: " << obj->hasFeature(QSqlDriver::DriverFeature::Unicode);
        qInfo() << "PreparedQueries: " << obj->hasFeature(QSqlDriver::DriverFeature::PreparedQueries);
        qInfo() << "NamedPlaceholders: " << obj->hasFeature(QSqlDriver::DriverFeature::NamedPlaceholders);
        qInfo() << "PositionalPlaceholders: " << obj->hasFeature(QSqlDriver::DriverFeature::PositionalPlaceholders);
        qInfo() << "LastInsertId: " << obj->hasFeature(QSqlDriver::DriverFeature::LastInsertId);
        qInfo() << "BatchOperations: " << obj->hasFeature(QSqlDriver::DriverFeature::BatchOperations);
        qInfo() << "SimpleLocking: " << obj->hasFeature(QSqlDriver::DriverFeature::SimpleLocking);
        qInfo() << "LowPrecisionNumbers: " << obj->hasFeature(QSqlDriver::DriverFeature::LowPrecisionNumbers);
        qInfo() << "EventNotifications: " << obj->hasFeature(QSqlDriver::DriverFeature::EventNotifications);
        qInfo() << "FinishQuery: " << obj->hasFeature(QSqlDriver::DriverFeature::FinishQuery);
        qInfo() << "MultipleResultSets: " << obj->hasFeature(QSqlDriver::DriverFeature::MultipleResultSets);
        qInfo() << "CancelQuery: " << obj->hasFeature(QSqlDriver::DriverFeature::CancelQuery);
        qInfo() << "";
    }

}

bool testPlugin()
{
    qInfo() <<"Testing plugin";
    QPluginLoader loader("C:/Qt/6.5.2/mingw_64/plugins/sqldrivers/qsqlite.dll");

    qInfo() << loader.metaData();

    if(loader.load())
    {
        qInfo() <<"Loaded the plugin";
        return true;
    }

    qInfo() << loader.errorString();
    return false;
}

int main(int argc, char *argv[])
{
    set_qt_environment();

    QGuiApplication app(argc, argv);

    if(testPlugin())
    {
        connectDB();
    }
    QQmlApplicationEngine engine;

    const QUrl url(u"qrc:Main/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    engine.load(url);

    // Example data
    QString machineId = "Machine123";
    double hopperTemp = 75.0;
    double cylinderTemp = 150.0;

    //writeToDatabase(machineId, hopperTemp, cylinderTemp);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
