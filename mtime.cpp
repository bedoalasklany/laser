#include "mtime.h"

MTime::MTime()
{
  h=0;m=0;s=0;
  secondes=0;
}
MTime::MTime(unsigned long long h,unsigned long long m,unsigned long long s)
{
    this->h=h;
    this->m=m;
    this->s=s;
    toSec();
}
unsigned long long MTime::toSec()
{
   this->secondes= h * 60 * 60 + m * 60 + s;
   return this->secondes;
}
void MTime::fromSec(unsigned long long sec)
{
    this->s=sec%60;
    this->m=(sec/60)%60;
    this->h=(sec/3600);
    toSec();
}
void MTime::fromstring(QString t)
{
    sscanf(t.toStdString().c_str(),"%llu:%llu:%llu",&h,&m,&s);
    this->toSec();
}
QString MTime::toString()
{
 QString st;
 if(this->h>99)
        st.sprintf("%03llu:%02llu:%02llu",this->h,this->m,this->s);
 else
        st.sprintf("%02llu:%02llu:%02llu",this->h,this->m,this->s);
 return  st;

}
