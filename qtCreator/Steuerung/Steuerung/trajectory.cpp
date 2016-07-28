#include "trajectory.h"
#include <QtCore>

#include <iostream>

Trajectory::Trajectory(QObject *parent) :
    QThread(parent)
{
}

Trajectory::Trajectory( QListWidget *list ){
   this->list = list;
    shared_mem_id = shmget(SMkey, SMsize, 0666);;

    shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
    shmdt(shared_mem);

}

void Trajectory::run(){
    std::cout << "Trajectory Thread" << std::endl;
    int phi_b, phi_c;
    char command;
    char * pch;
    char * text;
    char posAngefahren;

    text = (char *)malloc(100);
    for( int i = 0; i < list->count(); i++){
       list->setCurrentRow(i);
       text = list->item(i)->text().toAscii().data();
       std::cout << text << "\n";
       pch = strtok(text, " ");
       command = pch[0];
       if( command == 'A' ){
          pch = strtok(NULL, " ");
          phi_b = atoi( pch );
          pch = strtok(NULL, " ");
          phi_c = atoi( pch );
          std::cout << "Command: " << command << " b: " << phi_b << " c: " << phi_c << std::endl;
          shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
          shared_mem->phi_b_soll = phi_b;
          shared_mem->phi_c_soll = phi_c;
          shmdt(shared_mem);
          posAngefahren = 0;
          do{
            usleep(1000);
            shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
            posAngefahren = shared_mem->phi_b == shared_mem->phi_b_soll &&
                            shared_mem->phi_c == shared_mem->phi_c_soll;
            shmdt(shared_mem);
          }while( !posAngefahren );
       }
       if( command == 'U'){
          std::cout << "UP" << std::endl;
          shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
          shared_mem->UP = 1;
          shmdt(shared_mem);
          sleep(1);
       }
       if( command == 'D'){
          std::cout << "DOWN" << std::endl;
          shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
          shared_mem->UP = 0;
          shmdt(shared_mem);
          sleep(1);
          // D: nach unten fahren
       }


    }

}

