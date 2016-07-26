#include "trajectory.h"
#include <QtCore>
#include <iostream>

Trajectory::Trajectory(QObject *parent) :
    QThread(parent)
{
}

Trajectory::Trajectory( QListWidget *list ){
   this->list = list;
}

void Trajectory::run(){
    std::cout << "Trajectory Thread" << std::endl;
    int phi_b, phi_c;
    char command;
    char * pch;
    char * text;

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
          //TODO:
          // A: set phi_b und phi_c als soll
          //    wait for phi_b und phi_c ist
       }
       if( command == 'U'){
          std::cout << "UP" << std::endl;
           // U: nach oben fahren
       }
       if( command == 'D'){
          std::cout << "DOWN" << std::endl;
          // D: nach unten fahren
       }

       sleep(1);
    }

}

