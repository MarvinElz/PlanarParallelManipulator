/*
   

   g++ motor.c -std=c++0x -o motor -pthread -lwiringPi
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
   int offset_phi_soll;
   int offset_phi_ist;
} typedef motor;

struct PINS{
	int step;
	int dir;
	int sleep;
	char mot_number;
} typedef PINS;

volatile motor mot = {0,0,0,0,0};
PINS  pins;

void init( int number ){
   if( number == 1 ){
      pins = { PIN_mot1_step, PIN_mot1_dir, PIN_mot1_sleep, 1 };	
      mot.offset_phi_soll = offset_phi_b_soll;
      mot.offset_phi_ist  = offset_phi_b;
   }
   else{
      pins = { PIN_mot2_step, PIN_mot2_dir, PIN_mot2_sleep, 2 };
      mot.offset_phi_soll = offset_phi_c_soll;
      mot.offset_phi_ist  = offset_phi_c;
   }      
   pinMode ( pins.step , OUTPUT );
   pinMode ( pins.dir  , OUTPUT );
   pinMode ( pins.sleep, OUTPUT );
}


void run(){
   unsigned long delta;
   while(1){   	  
      if( mot.speed != 0 ){
         delta = 200000 / mot.speed;      // speed [0..100] -> f = 2.5Hz .. 250Hz
         digitalWrite( pins.step , LOW );
         usleep( delta );  
         digitalWrite( pins.step, HIGH );
         usleep( delta );
      }else
         usleep(1000);     
                    
   }
} 


int main( int argc, const char* argv[] ){
	int mot_Number;
   if( argc < 2 ){
      cout << "Bitte mindestens einen Parameter übergeben zur Auswahl des Encoders" << endl;
      return 1;  // mindestens ein Parameter muss übergeben werden
    }
   if (sscanf (argv[1], "%i", &mot_Number)!=1){
     cout << "Parameter konnte nicht gelesen werden" << endl;
     return 2;
   }
   cout << "Motor Nr.: " << mot_Number << endl;

   wiringPiSetup();
   init( mot_Number );
   shared_mem_id = shmget(SMkey, SMsize, 0666);

   std::thread go(run);
   cout << "Thread gestartet" << endl;
   int *phi_soll;
   int *phi_ist;

   while(1){
      shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);  // Zugriff auf shared memory bekommen
      phi_soll = (int *)((char *)shared_mem + mot.offset_phi_soll );  // Pointer auf shared_mem + offset = Pointer auf phi_b_soll, bzw. phi_c_soll
      phi_ist = (int *)((char *)shared_mem + mot.offset_phi_ist );  // Pointer auf shared_mem + offset = Pointer auf phi_b_soll, bzw. phi_c_soll
      int delta = *phi_soll - *phi_ist;
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
      digitalWrite( pins.dir, dir );
      if( delta > 100 )
         delta = 100;
      mot.speed = delta;
      usleep(10000);  // 10ms warten

      

   }

}