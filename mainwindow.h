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

private:
    Ui::MainWindow *ui;
    QList<Laser_file*> files_pathe;
    int num_files=0;

    Laser_file* processfile(QString path);
    std::string trim(const std::string& str, const std::string& whitespace = " \t");
    void perform();
};

#endif // MAINWINDOW_H
