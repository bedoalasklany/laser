/*
Name: QtRpt
Version: 2.0.2
Web-site: http://www.qtrpt.tk
Programmer: Aleksey Osipov
E-mail: aliks-os@ukr.net
Web-site: http://www.aliks-os.tk

Copyright 2012-2018 Aleksey Osipov

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef RPTSQL_H
#define RPTSQL_H

#include <QObject>
#include <QSqlQuery>
#include <QImage>

struct RptSqlConnection
{
    bool active;
    QString dsName;
    QString dbType;
    QString dbName;
    QString dbHost;
    QString dbUser;
    QString dbPassword;
    int dbPort;
    QString dbConnectionName;
    QString sqlQuery;
    QString dbCoding;
    QString charsetCoding;
};

class RptSql : public QObject
{
    Q_OBJECT
public:
    explicit RptSql(RptSqlConnection connection, QObject *parent = 0);
    bool openQuery(QString sql, QString dbCoding, QString charsetCoding);
    int getRecordCount();
    QString getFieldValue(QString fieldName, int recNo);
    QImage getFieldImage(QString fieldName, int recNo);

private:
    QSqlDatabase db;
    QSqlQuery *query;

signals:

public slots:

};

#endif // RPTSQL_H
