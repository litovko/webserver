#include "cdatabase.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>

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


    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("192.168.224.57");
    //db.setHostName("127.0.0.0");
        db.setDatabaseName("dsydb");
        db.setUserName("postgres");
        db.setPassword("12345678");
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
        else {
            qDebug() << "cannot open DB";
            qDebug() << db.lastError();
        }

}

QByteArray cDatabase::login(stefanfrings::HttpRequest &request)
{
    //curl -d {\"login\":\"user\",\"password\":\"user\"}  -H "Content-type: application/json; charset=utf-8" -H "Accept: application/json"  https://localhost/api/v1/login?appid=FFF01 -k
    //QSqlDatabase dbc=db.cloneDatabase();
    //auto db = QSqlDatabase::addDatabase( "QPSQL","db_conn_login");
    auto db=get_db();
    qDebug()<<"adding DB";
    // open the database, setup tables, etc.
//    db.setHostName("192.168.224.57");
//    db.setDatabaseName("dsydb");
//    db.setUserName("postgres");
//    db.setPassword("12345678");
    qDebug()<<"isvalid db:"<<db.isValid()<<"isopen DB:"<<db.isOpen();
    if (!db.isOpen()) db.open();
    qDebug()<<"isvalid db:"<<db.isValid()<<"isopen DB:"<<db.isOpen();
    //if(!isopen()) return "db error";
    qDebug()<<"==login";
    qDebug()<<"body:"<<request.getBody();
    QJsonDocument doc = QJsonDocument::fromJson(request.getBody());
    if (doc.isNull()) qWarning()<<"bad parsing";
    qDebug()<<"object:"<<doc.object();
    //check login field
    //construct SQL query
    QSqlQuery query("select f_login('user', 'user')",db);
    //execute
    qWarning() << query.value(0).toString();
    //get results
    //if exists then create tocken
    // writedown tocken to DB

    return doc.toJson(QJsonDocument::Indented);
}

QSqlDatabase cDatabase::get_db()
{
    auto name = "my_db_" + QString::number((quint64)QThread::currentThread(), 16);
    qDebug()<<"db_name:"<<name;
    if(QSqlDatabase::contains(name))
        return QSqlDatabase::database(name);
    else {
        auto db = QSqlDatabase::addDatabase( "QPSQL", name);
        qDebug()<<"adding DB";
        // open the database, setup tables, etc.
        db.setHostName("192.168.224.57");
        db.setDatabaseName("dsydb");
        db.setUserName("postgres");
        db.setPassword("12345678");
        db.open();
        return db;
    }
}
