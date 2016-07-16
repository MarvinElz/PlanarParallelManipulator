/*
   


*/

#include "shrd_mem.h"
#include <wiringPi.h>
#include <thread>
#include <iostream>
#include <unistd.h>  // usleep()

struct Motor{
	unsigned char speed;
	char dir;
	char sleep;
} typdef motor;

struct PINS{
	int step;
	int dir;
	int sleep;
	char mot_number;
} typedef PINS;

motor mot = {0, 0, 0};
PINS  pins;

void init( int number ){
   if( number == 1 )
      pins = { PIN_mot1_step, PIN_mot1_dir, PIN_mot1_sleep, 1 };	
   else
      pins = { PIN_mot2_step, PIN_mot2_dir, PIN_mot2_sleep, 2 };
   pinMode ( pins.step , Output );
   pinMode ( pins.dir  , Output );
   pinMode ( pins.sleep, Output );
}


void run(){
  // unsigned long delta;
   while(1){   	  
  /*	  if( speed != 0 ){
         digitalWrite( pins.step , LOW );
         usleep( 1000000 / mot.speed );  // speed [0..100] -> f = 0.5Hz .. 50Hz
         digitalWrite( pins.step, HIGH );
         usleep( 1000000 / mot.speed );
      }else
         usleep(1000);     
         */
      cout << mot.speed << endl;   
      usleep(1000000);    
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
   	  //TODO: 
      sleep(100);
      mot.speed++;

   }

}