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
void MainWindow::  openDir()
{
  QString dirname = QFileDialog::getExistingDirectory(
      this,
      tr("Select a Directory"),
      /*QDir::currentPath()*/ "D:\\Projects\\MDB 126" );
  if( !dirname.isNull() )
  {
    qDebug()<< dirname;
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
       files_pathe.push_back(temp);
       ui->listWidget->addItem(temp);
       num_files++;
   }
   ui->num_files->display(num_files);



}
