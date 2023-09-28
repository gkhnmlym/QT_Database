#include "database.h"

Database::Database()
{
}

bool Database::openDatabase(const QString &path)
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

bool Database::createTable()
{
    QString query = "CREATE TABLE IF NOT EXISTS testtable ("
                    "machineId INTEGER NOT NULL,"
                    "password INTEGER NOT NULL,"
                    "cylinderUp INTEGER NOT NULL,"
                    "hopperUp INTEGER NOT NULL,"
                    "cylinderSet INTEGER NOT NULL,"
                    "hopperSet INTEGER NOT NULL,"
                    "pressureLow REAL NOT NULL,"
                    "pressure REAL NOT NULL,"
                    "pressureLowSelf REAL NOT NULL,"
                    "pressureHighSelf REAL NOT NULL,"
                    "pressureFluidSelf REAL NOT NULL,"
                    "pressureFluid REAL NOT NULL,"
                    "iceCreamHardness REAL NOT NULL,"
                    "iceCreamCount INTEGER NOT NULL,"
                    "washDay INTEGER NOT NULL);";

    QSqlQuery qry;

    if (!qry.exec(query))
    {
        qDebug() << "Error creating table";
        return false;
    }

    qDebug() << "Table created";
    return true;
}

bool Database::addValues(int machineId, int password, int cylinderUp,
                         int hopperUp,int cylinderSet, int hopperSet,
                         double pressureLow, double pressure, double pressureLowSelf,
                         double pressureHighSelf, double pressureFluidSelf, double pressureFluid,
                         double iceCreamHardness,int iceCreamCount, int washDay)
{
    QSqlQuery qry;
    qry.prepare("INSERT INTO testtable ("
                "machineId, password, cylinderUp, hopperUp, cylinderSet,hopperSet,pressureLow,pressure, pressureLowSelf,pressureHighSelf,pressureFluidSelf,pressureFluid,iceCreamHardness,iceCreamCount,washDay) "
                "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");

    qry.addBindValue(machineId);
    qry.addBindValue(password);
    qry.addBindValue(cylinderUp);
    qry.addBindValue(hopperUp);
    qry.addBindValue(cylinderSet);
    qry.addBindValue(hopperSet);
    qry.addBindValue(pressureLow);
    qry.addBindValue(pressure);
    qry.addBindValue(pressureLowSelf);
    qry.addBindValue(pressureHighSelf);
    qry.addBindValue(pressureFluidSelf);
    qry.addBindValue(pressureFluid);
    qry.addBindValue(iceCreamHardness);
    qry.addBindValue(iceCreamCount);
    qry.addBindValue(washDay);

    if (!qry.exec())
    {
        qDebug() << "Error adding values to the database";
        return false;
    }

    return true;
}

bool Database::updateValues(int machineId, int newpassword, int newcylinderUp,
                            int newhopperUp,int newcylinderSet, int newhopperSet,
                            double newpressureLow, double newpressure, double newpressureLowSelf,
                            double newpressureHighSelf, double newpressureFluidSelf, double newpressureFluid,
                            double newiceCreamHardness,int newiceCreamCount, int newwashDay)
{
    QSqlQuery qry;
    qry.prepare("UPDATE testtable SET password = ?, cylinderUp = ?, hopperUp = ?, cylinderSet = ?, hopperSet = ?, pressureLow = ?, pressure = ?, pressureLowSelf = ?, pressureHighSelf = ?, pressureFluidSelf = ?, pressureFluid = ?, iceCreamHardness = ?, iceCreamCount = ?, washDay = ? WHERE machineId = ?;");


    qry.addBindValue(newpassword);
    qry.addBindValue(newcylinderUp);
    qry.addBindValue(newhopperUp);
    qry.addBindValue(newcylinderSet);
    qry.addBindValue(newhopperSet);
    qry.addBindValue(newpressureLow);
    qry.addBindValue(newpressure);
    qry.addBindValue(newpressureLowSelf);
    qry.addBindValue(newpressureHighSelf);
    qry.addBindValue(newpressureFluidSelf);
    qry.addBindValue(newpressureFluid);
    qry.addBindValue(newiceCreamHardness);
    qry.addBindValue(newiceCreamCount);
    qry.addBindValue(newwashDay);
    qry.addBindValue(machineId);

    if (!qry.exec())
    {
        qDebug() << "Error updating values in the database";
        return false;
    }

    return true;
}

void Database::closeDatabase()
{
    db.close();
}
