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
} typedef motor;

struct PINS{
	int step;
	int dir;
	int sleep;
	char mot_number;
} typedef PINS;

volatile motor mot = {0, 0, 0};
PINS  pins;

void init( int number ){
   if( number == 1 )
      pins = { PIN_mot1_step, PIN_mot1_dir, PIN_mot1_sleep, 1 };	
   else
      pins = { PIN_mot2_step, PIN_mot2_dir, PIN_mot2_sleep, 2 };
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

   init( mot_Number );

   std::thread go(run);

   while(1){
      sleep(1);      
      if( mot.speed < 100 )
	 mot.speed++;
      cout << (int)mot.speed << endl;
   }

}