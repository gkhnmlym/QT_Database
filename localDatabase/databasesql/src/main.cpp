#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "database.h"

bool initializeDatabase(Database &database) {
    qDebug() << "Start";

    if (!database.openDatabase("C:/Users/KEGMULAYIM/Documents/GitHub/QT_Database/localDatabase/database.db")) {
        qDebug() << "Exiting due to database open error";
        return false;
    }

    if (!database.createTable()) {
        qDebug() << "Exiting due to table creation error";
        return false;
    }
/*
    if (!database.addValues(12, 56, 46, 96, 96, 46, 46.0, 46.0, 56.0, 56.0, 96.0, 56.0, 56.0, 96, 46)) {
        qDebug() << "Exiting due to error adding values";
        return false;
    }
*/
    // Verileri güncelle
    if (database.updateValues(12, 56, 32, 26, 96, 46, 46.0, 46.0, 56.0, 56.0, 96.0, 56.0, 56.0, 96, 46)) {
        qDebug() << "Values updated successfully.";
    } else {
        qDebug() << "Error updating values.";
    }

    database.closeDatabase();

    qDebug() << "End";

    return true;
}

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    Database database;
    if (!initializeDatabase(database)) {
        return -1;
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

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
