#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QMainWindow>
#include <QDebug>
#include <QFileSystemModel>
#include <QDirModel>
#include <QDesktopServices>
#include <QList>

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
    QList<QString> files_pathe;
    void processfile(QString path);
    int num_files=0;
};

#endif // MAINWINDOW_H
