#include "worker.h"
//#include "shrd_mem.h"
#include <QtCore>



Worker::Worker(QObject *parent) :
    QThread(parent)
{
    shared_mem_id = shmget(SMkey, SMsize, 0666);
    shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
    shared_mem_local = (shared_mem_struct*)malloc(SMsize);
    memcpy(shared_mem_local, shared_mem, SMsize);
    shmdt(shared_mem);

}

void Worker::run(){
    printf("Started Thread\n");
    while(1){

    shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);

    if( shared_mem->phi_b != shared_mem_local->phi_b)
        emit phiBChanged(shared_mem->phi_b);
    if( shared_mem->phi_c != shared_mem_local->phi_c)
        emit phiCChanged(shared_mem->phi_c);
    if( shared_mem->phi_b_soll != shared_mem_local->phi_b_soll)
        emit phiBSollChanged(shared_mem->phi_b_soll);
    if( shared_mem->phi_c_soll != shared_mem_local->phi_c_soll)
        emit phiCSollChanged(shared_mem->phi_c_soll);

    memcpy(shared_mem_local, shared_mem, SMsize);
    shmdt(shared_mem);
    usleep(100000);

    }
}
