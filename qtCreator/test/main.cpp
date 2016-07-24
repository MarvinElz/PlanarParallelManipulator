#include "mainwindow.h"
#include <QApplication>
#include <thread>
#include <unistd.h>  // usleep()

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


