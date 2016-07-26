#ifndef WORKER_H
#define WORKER_H
#include "shrd_mem.h"
#include <QThread>
#include <QObject>

class Worker : public QThread
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);
    void run();

private:
    int shared_mem_id;
    shared_mem_struct * shared_mem;
    shared_mem_struct * shared_mem_local;


signals:
   void phiBChanged(int);
   void phiCChanged(int);
   void phiBSollChanged(int);
   void phiCSollChanged(int);
public slots:

};

#endif // WORKER_H
