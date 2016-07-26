#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "worker.h"
#include <QMainWindow>
#include <QListWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Worker *worker;

private slots:
    void on_b_reset_B_clicked();

    void on_b_reset_C_clicked();

    void on_b_B_up_pressed();

    void on_b_B_down_pressed();

    void on_b_C_up_pressed();

    void on_b_C_down_pressed();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

public slots:
    void onphiBChanged(int);
    void onphiCChanged(int);
    void onphiBSollChanged(int);
    void onphiCSollChanged(int);

private:
    Ui::MainWindow *ui;
    int shared_mem_id;
    shared_mem_struct * shared_mem;
   // static void ThreadRun( QListWidget *list );
};

#endif // MAINWINDOW_H
