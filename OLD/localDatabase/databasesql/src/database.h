#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

class Database
{
public:
    Database();
    bool openDatabase(const QString &path);
    bool createTable();
    bool addValues(int machineId, int password, int cylinderUp,
                      int hopperUp,int cylinderSet, int hopperSet,
                      double pressureLow, double pressure, double pressureLowSelf,
                      double pressureHighSelf, double pressureFluidSelf, double pressureFluid,
                      double iceCreamHardness,int iceCreamCount, int washDay);
    bool updateValues(int machineId, int newpassword, int newcylinderUp,
                      int newhopperUp,int newcylinderSet, int newhopperSet,
                      double newpressureLow, double newpressure, double newpressureLowSelf,
                      double newpressureHighSelf, double newpressureFluidSelf, double newpressureFluid,
                      double newiceCreamHardness,int newiceCreamCount, int newwashDay);
    void closeDatabase();

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
