#include "database.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


bool Database::initialize()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("daily_work_log.db");

    if(!db.open())
    {
        qDebug() << "Database Error:" << db.lastError().text();

        return false;
    }

    qDebug() << "Database connected successfully.";

    QSqlQuery query;

    QString sql = R"(
        CREATE TABLE IF NOT EXISTS work_logs
        (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            date TEXT NOT NULL,
            task TEXT NOT NULL,
            assigned_by TEXT,
            task_type TEXT,
            hours REAL NOT NULL,
            status TEXT,
            remarks TEXT
        )
           )";

    if(!query.exec(sql))
    {
        qDebug() << "Table creation error:"
                 << query.lastError().text();

        return false;
    }
    else
    {
        qDebug() << "work_logs table ready.";

        return true;
    }

}

QSqlDatabase Database::database()
{
    return QSqlDatabase::database();
}
