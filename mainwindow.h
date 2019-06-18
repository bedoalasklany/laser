#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QMainWindow>
#include <QDebug>
#include <QFileSystemModel>
#include <QDirModel>
#include <QDesktopServices>
#include <QList>
#include "laser_file.h"
#include <QFile>
#include <iostream>
#include <QHash>
#include <QTreeWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openDir();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QList<Laser_file*> file_list;
    int num_files=0;
    QHash <QString,QHash<QString,QList <Laser_file*> *> *> mat_list;

    Laser_file* processfile(QString path);
    std::string trim(const std::string& str, const std::string& whitespace = " \t");
    void classify();
    void addTreeRoot(QString name,QHash <QString, QList<Laser_file *> *>* dim_list);
    void addTreeChild(QTreeWidgetItem *parent, QList<Laser_file *> * list);
    void addTreeChild1(QTreeWidgetItem *parent, Laser_file * file);
};

#endif // MAINWINDOW_H
