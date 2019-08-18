#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>

#include "httprequest.h"

class cDatabase : public QObject
{
    Q_OBJECT
private:
    bool m_isopen=false;
public:
    explicit cDatabase(QObject *parent = nullptr);
signals:

public slots:
   QByteArray login(stefanfrings::HttpRequest& request);

public:
    QSqlDatabase db;
    bool isopen() const;
    void setIsopen(bool isopen);
};

#endif // DATABASE_H
