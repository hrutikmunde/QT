#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class Database
{
public:
    static bool initialize();
    static QSqlDatabase database();

};

#endif // DATABASE_H
