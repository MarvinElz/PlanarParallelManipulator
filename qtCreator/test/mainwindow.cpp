#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shrd_mem.h"

shared_mem_struct shared_mem_local;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    shared_mem_id = shmget(SMkey, SMsize, 0666);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_b_reset_B_clicked()
{
   shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
   shared_mem->phi_b      = atoi( ui->l_b_ist->text().toStdString().c_str() );
   shared_mem->phi_b_soll = atoi( ui->l_b_soll->text().toStdString().c_str() );
   shmdt(shared_mem);
}

void MainWindow::on_b_reset_C_clicked()
{
   shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
   shared_mem->phi_c      = atoi( ui->l_c_ist->text().toStdString().c_str() );
   shared_mem->phi_c_soll = atoi( ui->l_c_soll->text().toStdString().c_str() );
   shmdt(shared_mem);
}

void MainWindow::on_b_B_up_pressed()
{
    shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
    shared_mem->phi_b_soll++;
    if( shared_mem->phi_b_soll >= 960 ) shared_mem->phi_b_soll = 0;
    shmdt(shared_mem);
}

void MainWindow::on_b_B_down_pressed()
{
    shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
    shared_mem->phi_b_soll--;
    if( shared_mem->phi_b_soll < 0 ) shared_mem->phi_b_soll = 959;
    shmdt(shared_mem);
}

void MainWindow::on_b_C_up_pressed()
{
    shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
    shared_mem->phi_c_soll++;
    if( shared_mem->phi_c_soll >= 960 ) shared_mem->phi_c_soll = 0;
    shmdt(shared_mem);
}

void MainWindow::on_b_C_down_pressed()
{
    shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
    shared_mem->phi_c_soll--;
    if( shared_mem->phi_c_soll < 0 ) shared_mem->phi_c_soll = 959;
    shmdt(shared_mem);
}
