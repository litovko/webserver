#include "cdatabase.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>

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


    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
        db.setDatabaseName("dsydb");
        db.setUserName("lss");
        db.setPassword("123");
        setIsopen(db.open());

        if (isopen())
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

QByteArray cDatabase::login(stefanfrings::HttpRequest &request)
{
    //curl -d {\"login\":\"user\",\"password\":\"user\"}  -H "Content-type: application/json; charset=utf-8" -H "Accept: application/json"  https://localhost/api/v1/login?appid=FFF01 -k
    //QSqlDatabase dbc=db.cloneDatabase();
    if(!isopen()) return "db error";
    qDebug()<<"==login";
    qDebug()<<"body:"<<request.getBody();
    QJsonDocument doc = QJsonDocument::fromJson(request.getBody());
    if (doc.isNull()) qWarning()<<"bad parsing";
    qDebug()<<"object:"<<doc.object();
    //check login field
    //construct SQL query
    QSqlQuery query("select f_login('user', 'user')");
    //execute
    qWarning() << query.value(0).toString();
    //get results
    //if exists then create tocken
    // writedown tocken to DB

    return doc.toJson(QJsonDocument::Indented);
}
