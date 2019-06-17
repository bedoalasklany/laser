#ifndef LASER_FILE_H
#define LASER_FILE_H
#include <QtCore>
#include <QTime>

class Laser_file
{
public:
    Laser_file();
    Laser_file(QString path,QString material,QString thickness,int count ,QString sheet,QString total);
    QString path;
    QString material;
    QString thickness;
    int count;
    QString sheet_size;
    QTime total_time,time_120;

};

#endif // LASER_FILE_H
