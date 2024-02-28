// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"

#include "databasemanager.h"

int main(int argc, char *argv[])
{
    set_qt_environment();

    QGuiApplication app(argc, argv);

    // Database function
    DatabaseManager database;

    QString machineId = "12";

    if (!database.openDatabase("C:/Users/KEGMULAYIM/Desktop/QT/DATABASE/database.db")) {
        qDebug() << "Exiting due to database open error";
        return -1;
    }

    QMap<QString, QString> tableFields = {
        {"machineId", database.intValue},
        {"password", database.intValue},
        {"cylinderUp", database.intValue},
        {"hopperUp", database.intValue},
        {"cylinderSet", database.intValue},
        {"hopperSet", database.intValue},
        {"pressureLow", database.doubleValue},
        {"pressure", database.doubleValue},
        {"pressureLowSelf", database.doubleValue},
        {"pressureHighSelf", database.doubleValue},
        {"pressureFluidSelf", database.doubleValue},
        {"pressureFluid", database.doubleValue},
        {"iceCreamHardness", database.doubleValue},
        {"iceCreamCount", database.intValue},
        {"washDay", database.intValue}
    };

    if (!database.createTable("testtable", tableFields)) {
        qDebug() << "Exiting due to table creation error";
        return -1;
    }

    QMap<QString, QVariant> insertValues = {
        {"machineId", machineId},
        {"password", 56},
        {"cylinderUp", 46},
        {"hopperUp", 96},
        {"cylinderSet", 96},
        {"hopperSet", 46},
        {"pressureLow", 46.0},
        {"pressure", 46.0},
        {"pressureLowSelf", 56.0},
        {"pressureHighSelf", 56.0},
        {"pressureFluidSelf", 96.0},
        {"pressureFluid", 56.0},
        {"iceCreamHardness", 56.0},
        {"iceCreamCount", 96},
        {"washDay", 46}
    };

    QMap<QString, QVariant> updateValues = {
        {"password", 56},
        {"cylinderUp", 64},
        {"hopperUp", 26},
        {"cylinderSet", 96},
        {"hopperSet", 46},
        {"pressureLow", 46.0},
        {"pressure", 46.0},
        {"pressureLowSelf", 56.0},
        {"pressureHighSelf", 56.0},
        {"pressureFluidSelf", 96.0},
        {"pressureFluid", 56.0},
        {"iceCreamHardness", 56.0},
        {"iceCreamCount", 96},
        {"washDay", 46}
    };

//    if (!database.addValues("testtable", insertValues)) {
//        qDebug() << "Exiting due to error adding values";
//        return -1;
//    }

    if (database.updateValues("testtable", updateValues, "machineId = '" + machineId + "'")) {
        qDebug() << "Values updated successfully.";
    } else {
        qDebug() << "Error updating values.";
    }

    database.closeDatabase();

    qDebug() << "End";

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

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
