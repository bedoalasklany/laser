#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(5);
    QStringList a={"Material/Thickness","Sheets","Time","Time-120%","Quantity"};
    ui->treeWidget->setHeaderLabels(a);
    ui->treeWidget->setColumnWidth(0,200);
    ui->treeWidget->setColumnWidth(1,180);
    ui->treeWidget->setColumnWidth(2,180);
    ui->treeWidget->setColumnWidth(3,200);
    ui->treeWidget->setColumnWidth(4,30);

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
       file_list.push_back(processfile(temp));
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
         file->count=1;
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
     file->thickness=file->thickness.simplified()+" mm";
     file->sheet_size=file->sheet_size.simplified();
     temp_time=temp_time.simplified();
     file->total_time=QTime::fromString(temp_time, "HH:mm:ss");
     int  sec= QTime(0, 0, 0).secsTo(file->total_time);
     sec-= sec*.2;
     file->time_120=QTime(0, 0, 0).addSecs(sec);

     //std::cout<<file->path.toStdString();
     std::cout<<"\t"<<file->material.toStdString();
     std::cout<<"\t"<<file->thickness.toStdString();
     std::cout<<"\t"<<file->sheet_size.toStdString()<<"\t";
     //std::cout<<sec;
     std::cout<<"\t"<<file->total_time.toString().toStdString();
     std::cout<<"\t"<<file->time_120.toString().toStdString()<<std::endl;
     return file;
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

 void MainWindow::classify()
 {
      std::cout<<"number of files :"<<file_list.size()<<std::endl;
    for (int i=0;i<num_files;i++)
    {
        if(( mat_list.find(file_list[i]->material)== mat_list.end()  ) )
        {
            std::cout<<"creating new .................."<<std::endl;
            QHash  <QString , QList <Laser_file*> *> *dim_list=new QHash  <QString,QList <Laser_file*> *> ;
            if(dim_list==nullptr) std::cout<<"null.................."<<std::endl;
            QList <Laser_file*> * node_list=new QList <Laser_file*> ;
            std::cout<<"pushing in file list .................."<<std::endl;
            node_list->push_back(file_list[i]);
            std::cout<<"pushing in list in thickness list .................."<<std::endl;
            std::cout<<node_list->size()<<std::endl;
            dim_list->insert(file_list[i]->thickness,node_list);
            std::cout<<"pushing in thickness in material list .................."<<std::endl;
            mat_list.insert(file_list[i]->material,dim_list);

        }
        else if (mat_list.value(file_list[i]->material)->find(file_list[i]->thickness) == mat_list.value(file_list[i]->material)->end() )
        {
            QList <Laser_file*> * node_list=new QList <Laser_file*> ;
            node_list->push_back(file_list[i]);
            mat_list.value(file_list[i]->material)->insert(file_list[i]->thickness,node_list);
        }
        else
        {
          mat_list.value(file_list[i]->material)->value(file_list[i]->thickness)->push_back(file_list[i]);
          std::cout<<"added  .................."<<std::endl;
        }
    }

 }




void MainWindow::on_pushButton_2_clicked()
{
    std::cout<<"trying to classifying data......."<<std::endl;
    classify();
    std::cout<<"data classified......."<<std::endl;
    std::cout<<"......................................................................"<<std::endl;
    std::cout<<"......................................................................"<<std::endl;
    std::cout<<"......................................................................"<<std::endl;
    std::cout<<"......................................................................"<<std::endl;
    std::cout<<"material size...................."<<mat_list.size()<< std::endl;
    for(auto i=mat_list.begin();i !=mat_list.end();++i)
    {
        std::cout<<i.key().toStdString()<<".........................."<<i.value()->size()<< std::endl;
        for(auto j=i.value()->begin();j!=i.value()->end();++j)
        {
             std::cout<<j.key().toStdString()<<".........................."<<j.value()->size()<< std::endl;
            for(auto k=j.value()->begin();k!=j.value()->end();++k)
            {
                Laser_file * f=*k;
                std::cout<<f->material.toStdString()<<"\t";
                std::cout<<f->thickness.toStdString()<<"\t";
                std::cout<<f->total_time.toString().toStdString()<<"\t";
                std::cout<<f->time_120.toString().toStdString()<<"\t";
                std::cout<<f->count<<std::endl;
            }
        }
       addTreeRoot(i.key(),i.value());
    }
}
void MainWindow::addTreeRoot(QString name,QHash <QString, QList<Laser_file *> *>* dim_list)
{
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    for(auto i=dim_list->begin();i!=dim_list->end();++i)
        addTreeChild(treeItem,i.value());
}

void MainWindow::addTreeChild(QTreeWidgetItem *parent,QList<Laser_file *> *list)
{   // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0 , );
    for(auto i=list->begin();i!=list->end();++i)
        addTreeChild1(treeItem,*i);
    parent->addChild(treeItem);
}
