/*
   bekommt einen Sollwert und Istwert und regelt über die Geschwindigkeit   
   g++ motor.c -std=c++0x -o motor -pthread -lwiringPi
   sudo ./motor 
   sudo ./motor -A
   sudo ./motor -B
*/

#include "shrd_mem.h"
#include "motor.h"
#include <stddef.h>	// for offsetof()
#include <wiringPi.h>
#include <thread>
#include <iostream>
#include <unistd.h>  // usleep()

using namespace std;

struct Motor{
	unsigned char speed;
	char dir;
	char sleep;
} typedef motor;


int offset_phi_ist;
int offset_phi_soll;
int PIN_mot_step;
int PIN_mot_dir;
int PIN_mot_sleep;

volatile motor mot = {0,1,0};

int init( int motNr ){  
   if( motNr == 1 ){
      PIN_mot_step  = PIN_mot1_step;
      PIN_mot_dir   = PIN_mot1_dir;
      PIN_mot_sleep = PIN_mot1_sleep;
      offset_phi_ist  = offsetof( shared_mem_struct, phi_b );
      offset_phi_soll = offsetof( shared_mem_struct, phi_b_soll );
   }else if( motNr == 2 ){
      PIN_mot_step  = PIN_mot2_step;
      PIN_mot_dir   = PIN_mot2_dir;
      PIN_mot_sleep = PIN_mot2_sleep;
      offset_phi_ist  = offsetof( shared_mem_struct, phi_c );
      offset_phi_soll = offsetof( shared_mem_struct, phi_c_soll );
   }else{
      cout << "motNr out of range: [1,2]" << endl;
      return 0;
   } 
   pinMode ( PIN_mot_step , OUTPUT );
   pinMode ( PIN_mot_dir  , OUTPUT );
   pinMode ( PIN_mot_sleep, OUTPUT );
   return 1;
}


void run(){
   unsigned long delta;
   if( mot.speed > 100 ) mot.speed = 100;
   while(1){   	  
      if( mot.speed != 0 ){
         delta = 200000 / mot.speed;      // speed [0..100] -> f = 2.5Hz .. 250Hz
         digitalWrite( PIN_mot_step , LOW );
         usleep( delta );  
         digitalWrite( PIN_mot_step, HIGH );
         usleep( delta );
      }else
         usleep(1000);     
                    
   }
} 


int main( int argc, const char* argv[] ){
   int motNr = 0; // 1:A, 2:B

   if( argc != 2 ){
      cout << "Keinen Motorparameter übergeben: nutze Motor A" << endl;
      motNr = 1;
   }
   if( argc == 2 ){
      if( argv[1][1] == 'A' ){
          cout << "Nutze Motor A" << endl;
          motNr = 1;
      }else
      if( argv[1][1] == 'B' ){
          cout << "Nutze Motor B" << endl;
          motNr = 2;
      }else
      {
         cout << argv[1][1] << " ist kein richtiger Parameter ('A' / 'B')" << endl;
         cout << "Nutze Motor A" << endl;
         motNr = 1;
      }   
   }
	
   wiringPiSetup();
   if( !init( motNr ) ){
      cout << "Fehler während init()" << endl;
      return 1;
   }
   shared_mem_id = shmget(SMkey, SMsize, 0666);

   std::thread go(run);

   cout << "Thread gestartet" << endl;

   int phi_ist;
   int phi_soll;
   int delta;
   int dir;

   while(1){
      shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);  // Zugriff auf shared memory bekommen

      phi_ist  = *(int *)( (char*)shared_mem + offset_phi_ist );
      phi_soll = *(int *)( (char*)shared_mem + offset_phi_soll );

      delta = phi_soll - phi_ist;
      shmdt(shared_mem); 
            
      if( delta >= 0 )
         dir = 1;
      else{
         dir = 0;
         delta = - delta;
      }
      digitalWrite( PIN_mot_dir, dir );
      if( delta > 100 )
         delta = 100;
      mot.speed = delta;
      usleep(10000);  // 10ms warten
   }

}