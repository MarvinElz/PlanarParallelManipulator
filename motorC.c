/*
   bekommt einen Sollwert und Istwert und regelt über die Geschwindigkeit
   
   g++ motorC.c -std=c++0x -o motorC -pthread -lwiringPi
*/

#include "shrd_mem.h"
#include "motor.h"
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


volatile motor mot = {0,1,0};

void init( void ){   
   pinMode ( PIN_mot2_step , OUTPUT );
   pinMode ( PIN_mot2_dir  , OUTPUT );
   pinMode ( PIN_mot2_sleep, OUTPUT );
}


void run(){
   unsigned long delta;
   while(1){   	  
      if( mot.speed != 0 ){
         delta = 200000 / mot.speed;      // speed [0..100] -> f = 2.5Hz .. 250Hz
         digitalWrite( PIN_mot2_step , LOW );
         usleep( delta );  
         digitalWrite( PIN_mot2_step, HIGH );
         usleep( delta );
      }else
         usleep(1000);     
                    
   }
} 


int main( int argc, const char* argv[] ){
	
   wiringPiSetup();
   init(  );
   shared_mem_id = shmget(SMkey, SMsize, 0666);

   std::thread go(run);
   cout << "Thread gestartet" << endl;
   int *phi_soll;
   int *phi_ist;


   // TODO: Kalibrierung
   digitalWrite( PIN_mot2_dir, 0 );
   mot.speed = 10;
   char licht_schranke = 0;
   do{  // wenn Ausleger schon über Lichtschranke steht
      shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);  // Zugriff auf shared memory bekommen 
      licht_schranke = shared_mem->licht_c;
      shmdt(shared_mem);
      usleep(1000); 
   }while( licht_schranke );
   do{ // warte solange, bis Ausleger über Lichtschranke ist
      shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);  // Zugriff auf shared memory bekommen 
      licht_schranke = shared_mem->licht_c;
      shmdt(shared_mem);
      usleep(100);
   }while( !licht_schranke );   
   mot.speed = 0;
   digitalWrite( PIN_mot2_dir, 1 );  


   while(1){
      shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);  // Zugriff auf shared memory bekommen
      
      int delta = shared_mem->phi_c_soll - shared_mem->phi_c;
      shmdt(shared_mem); 
      
      int dir;
      
      if( delta > 480 ){
         dir = 0;          // rechtserehung
         delta = 960 - delta;
      }else
      if( delta < -480 ){
         dir = 1;         // linksdrehung
         delta = 960 + delta;
      }else
      if( delta >= 0 )
         dir = 1;
      else{
         dir = 0;
         delta = - delta;
      }
      digitalWrite( PIN_mot2_dir, dir );
      if( delta > 100 )
         delta = 100;
      mot.speed = delta;
      usleep(10000);  // 10ms warten

      

   }

}