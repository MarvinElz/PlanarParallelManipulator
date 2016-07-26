#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shrd_mem.h"
#include <thread>
#include <unistd.h>  // usleep()
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <fstream>
#include <string>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->b_B_down->setAutoRepeat(true);
    ui->b_B_up->setAutoRepeat(true);
    ui->b_C_down->setAutoRepeat(true);
    ui->b_C_up->setAutoRepeat(true);

    shared_mem_id = shmget(SMkey, SMsize, 0666);
    shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
    ui->l_b_ist->setText(QString::number(shared_mem->phi_b));
    ui->l_c_ist->setText(QString::number(shared_mem->phi_c));
    ui->l_b_soll->setText(QString::number(shared_mem->phi_b_soll));
    ui->l_c_soll->setText(QString::number(shared_mem->phi_c_soll));
    shmdt(shared_mem);

    worker = new Worker(this);
    connect(worker, SIGNAL(phiBChanged(int)), this, SLOT(onphiBChanged(int)));
    connect(worker, SIGNAL(phiCChanged(int)), this, SLOT(onphiCChanged(int)));
    connect(worker,SIGNAL(phiBSollChanged(int)), this, SLOT(onphiBSollChanged(int)));
    connect(worker,SIGNAL(phiCSollChanged(int)), this, SLOT(onphiCSollChanged(int)));
    worker->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onphiBChanged(int i){
   ui->l_b_ist->setText(QString::number(i));
}

void MainWindow::onphiCChanged(int i){
   ui->l_c_ist->setText(QString::number(i));
}

void MainWindow::onphiBSollChanged(int i){
   ui->l_b_soll->setText(QString::number(i));
}

void MainWindow::onphiCSollChanged(int i){
   ui->l_c_soll->setText(QString::number(i));
}

void MainWindow::on_b_reset_B_clicked()
{
   shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
   shared_mem->phi_b      = atoi( ui->l_b_ist->text().toStdString().c_str() );
   shared_mem->phi_b_soll = atoi( ui->l_b_soll->text().toStdString().c_str() );
   if( shared_mem->phi_b      >= 960 || shared_mem->phi_b      < 0) shared_mem->phi_b      = 0;
   if( shared_mem->phi_b_soll >= 960 || shared_mem->phi_b_soll < 0) shared_mem->phi_b_soll = 0;
   shmdt(shared_mem);
}

void MainWindow::on_b_reset_C_clicked()
{
   shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
   shared_mem->phi_c      = atoi( ui->l_c_ist->text().toStdString().c_str() );
   shared_mem->phi_c_soll = atoi( ui->l_c_soll->text().toStdString().c_str() );
   if( shared_mem->phi_c      >= 960 || shared_mem->phi_c      < 0) shared_mem->phi_c      = 0;
   if( shared_mem->phi_c_soll >= 960 || shared_mem->phi_c_soll < 0) shared_mem->phi_c_soll = 0;
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

void MainWindow::on_pushButton_2_clicked()
{
   // load constructions from File
   //int phi_b, phi_c;
   //char command;
   QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Text (*.txt);;sonst (*.*)"));
   QFile infile(fileName);
   if(!infile.open(QIODevice::ReadOnly | QIODevice::Text))
       return;
   QTextStream in(&infile);
   while( !in.atEnd()){
       QListWidgetItem *item = new QListWidgetItem( in.readLine() );
       ui->listWidget->addItem( item );
   }
}

void ThreadRun( QListWidget *list ){
    std::cout << "Trajectory Thread" << std::endl;
    sleep(1);
    int phi_b, phi_c;
    char command;
    char * pch;
    char * text;

    text = (char *)malloc(100); // alles in Thread auslagern
    for( int i = 0; i < list->count(); i++){
       list->setCurrentRow(i);
       text = list->item(i)->text().toAscii().data();
       std::cout << text << "\n";
       pch = strtok(text, " ");
       command = pch[0];
       pch = strtok(NULL, " ");
       phi_b = atoi( pch );
       pch = strtok(NULL, " ");
       phi_c = atoi( pch );
       std::cout << "Command: " << command << " b: " << phi_b << " c: " << phi_c << std::endl;
       sleep(1);
    }
}

void MainWindow::on_pushButton_clicked()
{
    std::thread run(ThreadRun, ui->listWidget);
}
