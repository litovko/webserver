#include "cdatabase.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>\

#define DB_SERVER_HOST "192.168.224.57"
#define DB_USERNAME "postgres"
#define DB_USERPASS "12345678"


bool cDatabase::isopen() const
{
    return m_isopen;
}

void cDatabase::setIsopen(bool isopen)
{
    m_isopen = isopen;
}

cDatabase::cDatabase(QObject *parent) : QObject(parent)
{


    QSqlDatabase db = get_db();

        if (db.isOpen())
        {
            QSqlQuery query("select * from users;",db);
            while (query.next())
            {
                qWarning() << query.value(0).toString();
                qWarning() << query.value(1).toString();
                qWarning() << query.value(2).toString();
                qWarning() << query.value(3).toString();
            }

            qDebug() << query.lastError().text();
        }
        else {
            qDebug() << "cannot open DB";
            qDebug() << db.lastError();
        }

}

QByteArray cDatabase::login(stefanfrings::HttpRequest &request)
{
    //curl -d {\"login\":\"user\",\"password\":\"user\"}  -H "Content-type: application/json; charset=utf-8" -H "Accept: application/json"  https://localhost/api/v1/login?appid=FFF01 -k
    auto db=get_db();
    qDebug()<<"==login";
    qDebug()<<"body:"<<request.getBody();
    QJsonDocument doc = QJsonDocument::fromJson(request.getBody());
    if (doc.isNull()) qWarning()<<"bad parsing";
    qDebug()<<"object:"<<doc.object();
    //check login field
    //construct SQL query
    QSqlQuery query("select f_login('user', 'user')",db);

    //execute
    QJsonDocument ret;
    while (query.next()) {
        qWarning() << query.value(0) <<"ret string:"<<query.lastError();
        ret = QJsonDocument::fromJson(query.value(0).toString().toUtf8());
        qDebug()<<"jason answer:"<<ret.toJson(QJsonDocument::Indented);
    }
    //get results
    //if exists then create tocken
    // writedown tocken to DB

    return ret.toJson(QJsonDocument::Indented);
}

QSqlDatabase cDatabase::get_db()
{
    auto name = "my_db_" + QString::number((quint64)QThread::currentThread(), 16);
    qDebug()<<"db_name:"<<name;
    if(QSqlDatabase::contains(name))
        return QSqlDatabase::database(name);
    else {
        QSqlDatabase db = QSqlDatabase::addDatabase( "QPSQL", name);

        qDebug()<<"adding DB"<<QSqlDatabase::connectionNames();
        // open the database, setup tables, etc.
        db.setHostName(DB_SERVER_HOST);
        db.setDatabaseName("dsydb");
        db.setUserName(DB_USERNAME);
        db.setPassword(DB_USERPASS);
        db.open();
        return db;
    }
}
