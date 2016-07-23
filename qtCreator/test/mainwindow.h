#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_b_reset_B_clicked();

    void on_b_reset_C_clicked();

    void on_b_B_up_pressed();

    void on_b_B_down_pressed();

    void on_b_C_up_pressed();

    void on_b_C_down_pressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
