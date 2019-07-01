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
#include <QListWidgetItem>
#include <mtime.h>
#include <QtSql>
#include <sqlserver.h>

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

    void on_mat_list_itemPressed(QListWidgetItem *item);

    void on_thick_list_itemPressed(QListWidgetItem *item);

    void on_pushButton_4_clicked();

    void onProcessStarted();
    void onProcessFinished();
    void onProgressValueChanged(int progressValue);
    void onProgressMaxChanged(int progressMax);
private:
    Ui::MainWindow *ui;
    QList<Laser_file*> file_list;
    unsigned long long  num_files=0;
    QHash <QString,QHash<QString,QList <Laser_file*> *> *> mat_list;

    Laser_file* processfile(QString path);
    std::string trim(const std::string& str, const std::string& whitespace = " \t");
    void classify();

    QString sum_sheets_list(QString material,QString thick);
    QString sum_time_list(QString material,QString thick, unsigned long long &sec);
    QString sum_time120_list(QString material,QString thick, unsigned long long &sec);

    QString sum_sheets_mat(QString material);
    QString sum_time_mat(QString material, unsigned long long &sec);
    QString sum_time120_mat(QString material, unsigned long long &sec);


    QString sum_sheets();
    QString sum_time();
    QString sum_time120();





    };

#endif // MAINWINDOW_H
