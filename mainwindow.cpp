#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
  openDir();
}
void MainWindow::openDir()
{
  QString dirname = QFileDialog::getExistingDirectory(
      this,
      tr("Select a Directory"),
      /*QDir::currentPath()*/ "D:\\Projects\\MDB 126" );
  if( !dirname.isNull() )
  {
    //qDebug()<< dirname;
  }

   QDirModel *model = new QDirModel(this);
   QString home_files = dirname;
   QModelIndex homeIndex = model->index(home_files);
   ui->treeView->setModel(model);
   ui->treeView->setRootIndex(homeIndex);
   QDir dir(dirname);
   QDirIterator it(dirname, QStringList() << "*.nc", QDir::Files, QDirIterator::Subdirectories);
   while (it.hasNext())
   {
       //qDebug() << it.next();
       QString temp=it.next();
       files_pathe.push_back(processfile(temp));
       ui->listWidget->addItem(temp);
       num_files++;
   }
   ui->num_files->display(num_files);



}
 Laser_file* MainWindow:: processfile(QString path)
 {
  Laser_file* file=new Laser_file;
  file->path=path;
  QString s1="";
  int start=0,stop=0;;
  for(int i=path.length()-1;i>=0;i--)
  {
      if(path[i]=='-'){start=i; break;}
      if(path[i]=='.')stop=i;
      if(path[i]=='/')break;;
  }
     for(int i=start+1;i<(stop);i++)
         s1+=path[i];
     if(!s1.isEmpty())
        file->count=s1.toInt();
     else
         file->count=0;
     QFile f(path);
     if(!f.open(QIODevice::ReadOnly)) {

     }
     QTextStream in(&f);
     in.readLine();in.readLine();in.readLine();
     QString s2=in.readLine();
     file->material=QString::fromStdString(s2.toStdString().substr( s2.toStdString().find_first_of(':')+1 ,s2.toStdString().find_last_of(')')-s2.toStdString().find_first_of(':')-1 ));
     s2=in.readLine();
     file->thickness=QString::fromStdString(s2.toStdString().substr( s2.toStdString().find_first_of(':')+1 ,s2.toStdString().find_last_of(')')-s2.toStdString().find_first_of(':')-1 ));
     s2=in.readLine();
     file->sheet_size=QString::fromStdString(s2.toStdString().substr( s2.toStdString().find_first_of(':')+1 ,s2.toStdString().find_last_of(')')-s2.toStdString().find_first_of(':')-1 ));
     s2=in.readLine();
     QString temp_time=QString::fromStdString(s2.toStdString().substr( s2.toStdString().find_first_of(':')+1 ,s2.toStdString().find_last_of(')')-s2.toStdString().find_first_of(':')-1 ));
     f.close();
     file->path=file->path.simplified();
     file->material=file->material.simplified();
     file->thickness=file->thickness.simplified();
     file->sheet_size=file->sheet_size.simplified();
     temp_time=temp_time.simplified();
     file->total_time=QTime::fromString(temp_time, "HH:mm:ss");
     unsigned long  sec= QTime(0, 0, 0).secsTo(file->total_time);
     sec-= sec*.2;
     file->time_120=QTime(0, 0, 0).addSecs(sec);

     //std::cout<<file->path.toStdString();
     std::cout<<"\t"<<file->material.toStdString();
     std::cout<<"\t"<<file->thickness.toStdString();
     std::cout<<"\t"<<file->sheet_size.toStdString()<<"\t";
     //std::cout<<sec;
     std::cout<<"\t"<<file->total_time.toString().toStdString();
     std::cout<<"\t"<<file->time_120.toString().toStdString()<<std::endl;

 }
 std::string trim(const std::string& str,const std::string& whitespace = " \t")
 {
     const auto strBegin = str.find_first_not_of(whitespace);
     if (strBegin == std::string::npos)
         return ""; // no content

     const auto strEnd = str.find_last_not_of(whitespace);
     const auto strRange = strEnd - strBegin + 1;
     return str.substr(strBegin, strRange);
 }



