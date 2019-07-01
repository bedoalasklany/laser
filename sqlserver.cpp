#include "sqlserver.h"

sqlserver::sqlserver()
{


}
bool sqlserver::connect()
{
    if(!db.isOpen() && !db.isValid())
  {
        QString connectionTemplate = "DRIVER={SQL SERVER};SERVER=%1;DATABASE=%2;PORT=%3";

        QString connectionString = connectionTemplate.arg("123.0.0.11").arg("laser_managment").arg("1430");
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

        db.setDatabaseName(connectionString);
        db.setUserName("sa");
        db.setPassword("alasklany");

  if(db.open())
  {
      std::cout<<"connected"<<std::endl;
      return true;
  }
  else
  {
       std::cout<<"not connected"<<std::endl;
      return false;
  }
    }
    return false;
}
bool sqlserver::disconnect()
{
    if(db.isOpen() || db.isValid())
    {
    db.close();

    if(db.isOpen() || db.isValid())
        return false;
    else
        return true;
    }
    return false;
}
