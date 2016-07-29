/*
    liefert aktuelle Position der Winkel an das Hauptprogramm
    ueber shared-memory
    Ablaufsteuerung über Zustandsautomaten
    g++ encoderB.c -std=c++0x -o encoderB -pthread -lwiringPi
*/

#include "shrd_mem.h"
#include "encoder.h"
#include <wiringPi.h>
#include <thread>
#include <iostream>
#include <unistd.h>  // usleep()

using namespace std;

struct Zustand{		
	char outValue;
	char ai[4];
} typedef Zustand;

Zustand Automat[4] = {  
        {  1, { 0, 1, 2, 3 } },   // rechtsdrehung
	{  0, { 0, 1, 2, 3 } },   // linksdrehung
	{  1, { 1, 0, 3, 2 } },   // rechtsdrehung
	{  0, { 1, 0, 3, 2 } } }; // linksdrehung

struct Encoder{
  char state;
  char input;
  char input_old;
  long angle; 
  long angle_old;
} typedef encoder;

encoder enc;


int init( void ){
  
  enc = { 0, 0, 0, 0};  
	pinMode ( enc1_a, INPUT );
	pinMode ( enc1_b, INPUT );
  
}

void update(){
 while(1){
   if( enc.angle != enc.angle_old ){
      shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);  // Zugriff auf shared memory bekommen
   
      if( enc.angle_old != shared_mem->phi_b )  // änderung von außen
         enc.angle = shared_mem->phi_b;
      else 
         shared_mem->phi_b = enc.angle;  
      shmdt(shared_mem); 
      enc.angle_old = enc.angle;
      }
   usleep(1000);
   }
   
}

int main( int argc, const char* argv[] ){
   
   wiringPiSetup();
   init(  );
   shared_mem_id = shmget(SMkey, SMsize, 0666);

   new thread( update );

   while(1){

      enc.input = digitalRead( enc1_a ) << 1 | digitalRead( enc1_b );       
      
      if (enc.input != enc.input_old){    // wenn Änderung stattgefunden hat
         enc.input_old = enc.input;       // Eingabe speichern für Abgleich   
         cout << (int)enc.input << endl; 
         enc.state = Automat[enc.state].ai[enc.input]; // neuer Zustand wird aus dem Automaten ermittelt              
                  
         if( Automat[enc.state].outValue )
            enc.angle++;        
         else
            enc.angle--; 

         if( enc.angle >= 960 )
            enc.angle = 960 - enc.angle;
         if( enc.angle < 0 )   
            enc.angle = 960 + enc.angle;

	 
         
      }
      usleep(10);
   }
}
