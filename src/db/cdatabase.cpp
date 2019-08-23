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

QByteArray cDatabase::error(QString source, int code)
{
    auto str="{\n  'errorsource':'"+source+"',\n  'code':"+ QString::number(code)+"\n}";
    return QByteArray::fromStdString(str.toStdString());
}

cDatabase::cDatabase(QObject *parent) : QObject(parent)
{
    //    QSqlDatabase db = get_db();

    //        if (db.isOpen())
    //        {
//            QSqlQuery query("select * from users;",db);
//            while (query.next())
//            {
//                qWarning() << query.value(0).toString();
//                qWarning() << query.value(1).toString();
//                qWarning() << query.value(2).toString();
//                qWarning() << query.value(3).toString();
//            }

//            qDebug() << query.lastError().text();
//        }
//        else {
//            qDebug() << "cannot open DB";
//            qDebug() << db.lastError();
//        }

}

QByteArray cDatabase::login(stefanfrings::HttpRequest &request)
{
    //curl -d {\"login\":\"user\",\"password\":\"user\"}  -H "Content-type: application/json; charset=utf-8" -H "Accept: application/json"  https://localhost/api/v1/login?appid=FFF01 -k
    auto db=get_db();
    qDebug()<<"==login";
//    qDebug()<<"body:"<<request.getBody();
    QJsonDocument doc = QJsonDocument::fromJson(request.getBody());
    if (doc.isNull()) {
        qWarning()<<"bad parsing";
        return error("login", 1000);
    }
    qDebug()<<"object:"<<doc.object();
    //construct SQL query
    //execute
//    qDebug()<<doc["login"];
    QString sql="select f_login('"+doc["login"].toString()+"', '"+doc["password"].toString()+"')";
    qDebug()<<sql;
    QSqlQuery query(sql,db);

    //get results
    QJsonDocument ret;
    while (query.next()) {
        qWarning() << query.value(0) <<"ret string:"<<query.lastError();
        ret = QJsonDocument::fromJson(query.value(0).toString().toUtf8());
        qDebug()<<"jason answer:"<<ret.toJson(QJsonDocument::Indented);
    }
    //check login field
    if (ret.toJson(QJsonDocument::Indented)=="") return error("login", 1001);
    //if exists then create tocken
    // write down tocken to DB
    return ret.toJson(QJsonDocument::Indented);
}

QByteArray cDatabase::tasks(stefanfrings::HttpRequest &request, QString &path)
{
    QString sql;
    auto db=get_db();
    qDebug()<<Q_FUNC_INFO;
    QJsonDocument doc = QJsonDocument::fromJson(request.getBody());
    if (doc.isNull()) {
        qWarning()<<"bad parsing:"<<Q_FUNC_INFO;;
        return error("tasks", 1000);
    }
    if (path.contains("/list"))  //список задач, пока смотрим только для конкретного пользователя
    sql="select json_agg(s) tasks "
        "from (select t.id, t.uid, t.state_id, t.type, t.param from tasks t, users u where t.uid=u.id and u.pkey='"
            +doc["pkey"].toString()
            +"')s";
    else
        sql="select add_task(100,'"+request.getBody()+"')"; //тип задачи по умолчанию 100
    qDebug()<<"sql:"<<sql;
    QSqlQuery query(sql,db);
    QJsonDocument ret;
    while (query.next()) {
        qWarning() << query.value(0) <<"ret string:"<<query.lastError();
        if (query.value(0).toString().length()==0)
                    return error("tasks", 1003);
        ret = QJsonDocument::fromJson(query.value(0).toString().toUtf8());
        qDebug()<<"jason answer:"<<ret.toJson(QJsonDocument::Indented);
    }
    if (ret.toJson(QJsonDocument::Indented)=="") return error("tasks", 1001);
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
