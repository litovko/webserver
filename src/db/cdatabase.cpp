#include "cdatabase.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

cDatabase::cDatabase(QObject *parent) : QObject(parent)
{


    db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName("127.0.0.1");
        db.setDatabaseName("dsydb");
        db.setUserName("lss");
        db.setPassword("123");
        bool ok = db.open();

        if (ok)
        {
            QSqlQuery query("select * from users;");
            while (query.next())
            {
                qWarning() << query.value(0).toString();
                qWarning() << query.value(1).toString();
                qWarning() << query.value(2).toString();
                qWarning() << query.value(3).toString();
            }

            qDebug() << query.lastError().text();
        }
}
