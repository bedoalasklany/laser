#ifndef SQLSERVER_H
#define SQLSERVER_H
#include <QtCore>
#include <QSqlDatabase>
#include <iostream>

class sqlserver
{
private:
    QSqlDatabase db;
public:
    sqlserver();
    bool connect ();
    bool disconnect();

};

#endif // SQLSERVER_H
