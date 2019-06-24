#ifndef MTIME_H
#define MTIME_H
#include <QtCore>
#include <stdio.h>

class MTime
{
public:
    MTime();
    MTime(unsigned long long h,unsigned long long m,unsigned long long s);
    QString toString();
    void    fromstring(QString t);
    unsigned long long toSec();
    void fromSec(unsigned long long sec);
private:
    unsigned long long  h,m,s;
    unsigned long long secondes;
};

#endif // MTIME_H
