#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList a={"Sheets","Time","Time-120%","Quantity"};
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(a);
    ui->tableWidget->setColumnWidth(0,159);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(3,120);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);

        statusBar()->addPermanentWidget(ui->progressBar);
        ui->progressBar->hide();

        sqlserver sql;
sql.connect();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);

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
  else
      return;

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
   ui->num_files->display((int)num_files);
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
     if(file->count==0) file->count=1;
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
     MTime m;
     file->total_time.fromstring(temp_time);
     unsigned long long   sec= file->total_time.toSec() * file->count ;
     file->total_time.fromSec(sec);
     sec*=.8;
     file->time_120.fromSec(sec);

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
    for ( int  i=0;i<((int)num_files);i++)
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
        ui->mat_list->addItem(i.key());
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

    }

    ui->t_sheets->setText( sum_sheets());
    ui->t_time->setText(sum_time());
    ui->t_time120->setText( sum_time120());





}


void MainWindow::on_mat_list_itemPressed(QListWidgetItem *item)
{

  ui->thick_list->clear();
  QString s=item->text();
 QHash<QString,QList <Laser_file*> *> *temp=mat_list.value(s);

  for (auto i=temp->begin();i!=temp->end();++i)
  {
        ui->thick_list->addItem(i.key());
  }
  unsigned long long tempmx;
  ui->mat_sheetes->setText( sum_sheets_mat(s));
  ui->mat_time->setText(sum_time_mat(s,tempmx));
  ui->mat_time120->setText( sum_time120_mat(s,tempmx));



}

void MainWindow::on_thick_list_itemPressed(QListWidgetItem *item)
{

    QString s1=ui->mat_list->selectedItems().first()->text();
    QHash<QString,QList <Laser_file*> *> *temp1=mat_list.value(s1);
    QString s2=item->text();
    QList <Laser_file*> *temp2=temp1->value(s2);
    int row=0;
    ui->tableWidget->clear();
    QStringList a={"Sheets","Time","Time-120%","Quantity"};
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(a);
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(3,120);
    ui->tableWidget->setRowCount(0);
    for(auto j=(temp2)->begin();j !=(temp2)->end(); ++j)
    {
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row,0,new QTableWidgetItem((*j)->sheet_size));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem((*j)->total_time.toString()));
        ui->tableWidget->setItem(row,2,new QTableWidgetItem((*j)->time_120.toString()));
        ui->tableWidget->setItem(row,3,new QTableWidgetItem(QString::number((*j)->count)));
       /* ui->tableWidget->takeItem(row,0)->setTextAlignment( Qt:: AlignCenter);
        ui->tableWidget->takeItem(row,1)->setTextAlignment( Qt:: AlignCenter);
        ui->tableWidget->takeItem(row,2)->setTextAlignment( Qt:: AlignCenter);
        ui->tableWidget->takeItem(row,3)->setTextAlignment(Qt:: AlignCenter);*/
        row++;

    }
    unsigned long long tempmx;
     ui->thick_t_sheetes->setText( sum_sheets_list(s1,s2));
     ui->thick_t_total_time->setText(sum_time_list(s1,s2,tempmx));
     ui->thick_t_time120->setText( sum_time120_list(s1,s2,tempmx));



    /* std::cout<<sum_sheets_list(s1,s2).toStdString()<<"\t";
     std::cout<<sum_time_list(s1,s2).toStdString()<<"\t";
     std::cout<<sum_time120_list(s1,s2).toStdString()<<std::endl;*/


}

QString MainWindow::sum_sheets_list(QString material, QString thick)
{
    unsigned long long  sum=0;
   for(auto i= mat_list.value(material)->value(thick)->begin();i != mat_list.value(material)->value(thick)->end();++i )
   {
       sum += 1 * (*i)->count;
   }

   return QString::number(sum);
}
QString MainWindow::sum_time_list(QString material, QString thick, unsigned long long &sec)
{
  unsigned long long   time=0;
  MTime m;
  for(auto i= mat_list.value(material)->value(thick)->begin();i != mat_list.value(material)->value(thick)->end();++i )
  {
      time += (*i)->total_time.toSec();
  }
  sec=time;
  m.fromSec(time);
  return
          m.toString();
}
QString MainWindow::sum_time120_list(QString material, QString thick, unsigned long long &sec)
{
    unsigned long long   time=0;
    MTime m;
    for(auto i= mat_list.value(material)->value(thick)->begin();i != mat_list.value(material)->value(thick)->end();++i )
    {
        time += (*i)->time_120.toSec();
    }
    sec=time;
    m.fromSec(time);
    return
            m.toString();
}


QString MainWindow::sum_sheets_mat(QString material)
{
   int sum=0;

   for(auto i= mat_list.value(material)->begin();i != mat_list.value(material)->end();++i )
   {
     sum+= sum_sheets_list(material,i.key()).toInt();
   }

   return QString::number(sum);
}
QString MainWindow::sum_time_mat(QString material, unsigned long long &sec)
{
  unsigned long long  time=0,sec_in;
  MTime m;
  for(auto i= mat_list.value(material)->begin();i != mat_list.value(material)->end();++i )  {
      sum_time_list(material,i.key(),sec_in);
      time +=sec_in;
  }
   sec=time;
   m.fromSec(time);
  return
          m.toString();
}
QString MainWindow::sum_time120_mat(QString material, unsigned long long &sec)
{
    unsigned long long  time=0,sec_in;
    MTime m;
  for(auto i= mat_list.value(material)->begin();i != mat_list.value(material)->end();++i )  {
      sum_time120_list(material,i.key(),sec_in);
      time +=sec_in;
  }
 sec=time;
  m.fromSec(time);
 return
         m.toString();
}


QString MainWindow::sum_sheets()
{
    int sum=0;
 for(auto i=mat_list.begin();i!= mat_list.end();++i)
 {
   sum+=sum_sheets_mat(i.key()).toInt();
 }
 return  QString::number(sum);
}

QString MainWindow::sum_time()
{
    unsigned long long  time=0,sec_in;
    MTime m;
 for(auto i=mat_list.begin();i!= mat_list.end();++i)
 {
     sum_time_mat(i.key(),sec_in);
     time +=sec_in;
 }

 m.fromSec(time);
return
        m.toString();
}

QString MainWindow::sum_time120()
{
    unsigned long long  time=0,sec_in;
    MTime m;
 for(auto i=mat_list.begin();i!= mat_list.end();++i)
 {
     sum_time120_mat(i.key(),sec_in);
     time +=sec_in;

 }
 m.fromSec(time);
return
        m.toString();
}



void MainWindow::on_pushButton_4_clicked()
{
    if(!ui->proj_name_edit->text().isEmpty())
    {
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    }
}






void MainWindow::onProcessStarted()
{
    ui->progressBar->show();
}

void MainWindow::onProcessFinished()
{
     ui->progressBar->hide();
}

void MainWindow::onProgressValueChanged(int progressValue)
{
     ui->progressBar->setValue(progressValue);
}

void MainWindow::onProgressMaxChanged(int progressMax)
{
     ui->progressBar->setMaximum(progressMax);
}
