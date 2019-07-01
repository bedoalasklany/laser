#ifndef LASER_PROJECT_H
#define LASER_PROJECT_H
#include <QDateTime>
#include <mtime.h>
#include <laser_file.h>
class laser_project
{
public:
    laser_project();
    QString Name;
    QDateTime history;
    unsigned long long quantity;
    MTime time,time_120;
    QHash <QString,QHash<QString,QList <Laser_file*> *> *> mat_list;


};

#endif // LASER_PROJECT_H
