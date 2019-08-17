#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>

class cDatabase : public QObject
{
    Q_OBJECT
public:
    explicit cDatabase(QObject *parent = nullptr);

signals:

public slots:

public:
    QSqlDatabase db;
};

#endif // DATABASE_H
