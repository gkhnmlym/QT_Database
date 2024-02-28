#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>
#include <QObject>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    bool openDatabase(const QString &path);
    bool createTable(const QString &tableName, const QMap<QString, QString> &fields);
    bool addValues(const QString &tableName, const QMap<QString, QVariant> &values);
    bool updateValues(const QString &tableName, const QMap<QString, QVariant> &values, const QString &condition); // Değişiklik burada
    void closeDatabase();

    static const QString intValue;
    static const QString doubleValue;

private:
    QSqlDatabase db;

signals:

};

#endif // DATABASEMANAGER_H
