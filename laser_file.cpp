#include "laser_file.h"

 Laser_file::Laser_file(QString path,QString material,QString thickness,int count ,QString sheet,QString total)
{
   this->material=material;
   this->path=path;
    this->thickness=thickness;
   this->count=count;
   this->sheet_size=sheet;
}
Laser_file::Laser_file()
{
  count=1;
}
