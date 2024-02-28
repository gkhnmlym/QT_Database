#include "databasemanager.h"

const QString DatabaseManager::intValue = "INTEGER NOT NULL";
const QString DatabaseManager::doubleValue = "REAL NOT NULL";


DatabaseManager::DatabaseManager(QObject *parent) : QObject{parent}
{

}

bool DatabaseManager::openDatabase(const QString &path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open())
    {
        qDebug() << "Problem opening the database";
        return false;
    }

    return true;
}

bool DatabaseManager::createTable(const QString &tableName, const QMap<QString, QString> &fields)
{
    QString query = "CREATE TABLE IF NOT EXISTS " + tableName + "(";
    QStringList fieldList;
    for (auto it = fields.constBegin(); it != fields.constEnd(); ++it) {
        fieldList.append(it.key() + " " + it.value());
    }
    query += fieldList.join(", ");
    query += ");";

    QSqlQuery qry;

    if (!qry.exec(query))
    {
        qDebug() << "Error creating table";
        return false;
    }

    qDebug() << "Table created";
    return true;
}

bool DatabaseManager::addValues(const QString &tableName, const QMap<QString, QVariant> &values)
{
    QSqlQuery qry;
    qry.prepare("INSERT INTO " + tableName + " VALUES(" + QString("?,").repeated(values.size()-1) + "?)");

    for (auto it = values.constBegin(); it != values.constEnd(); ++it)
        qry.addBindValue(it.value());

    if (!qry.exec())
    {
        qDebug() << "Error adding values to the database";
        return false;
    }

    return true;
}

bool DatabaseManager::updateValues(const QString &tableName, const QMap<QString, QVariant> &values, const QString &condition)
{
    QString query = "UPDATE " + tableName + " SET ";
    QStringList updateList;
    for (auto it = values.constBegin(); it != values.constEnd(); ++it)
        updateList.append(it.key() + " = ?");
    query += updateList.join(", ");
    query += " WHERE " + condition + ";";

    QSqlQuery qry;
    qry.prepare(query);

    for (auto it = values.constBegin(); it != values.constEnd(); ++it)
        qry.addBindValue(it.value());

    if (!qry.exec())
    {
        qDebug() << "Error updating values in the database";
        return false;
    }

    return true;
}

void DatabaseManager::closeDatabase()
{
    db.close();
}
