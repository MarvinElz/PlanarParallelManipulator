/*
    liefert aktuelle Position der Winkel an das Hauptprogramm
    ueber shared-memory
    Ablaufsteuerung über Zustandsautomaten
    g++ encoder.c -std=c++0x -o encoder -pthread -lwiringPi
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
  char a;
  char b;
  long angle; 
  char number;
  int offset; // Zugriff auf phi_b, bzw. phi_c
} typedef encoder;

encoder enc;


int init(int enc_Number){
  if( enc_Number == 1 )  
     enc = { 0, 0, 0, enc1_a, enc1_b, 0, 1, offset_phi_b};
  if( enc_Number == 2 )   
     enc = { 0, 0, 0, enc2_a, enc2_b, 0, 2, offset_phi_c };
	pinMode ( enc.a, INPUT );
	pinMode ( enc.b, INPUT );
  
}

void update(){
   cout << "update anfang" << endl;
   int *phi;
   shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);  // Zugriff auf shared memory bekommen
   
   phi = (int *)((char *)shared_mem + enc.offset );  // Pointer auf shared_mem + offset = Pointer auf phi_b, bzw. phi_b
   if( *phi > 960  )  // Rücksetzimpuls
      enc.angle = 0;   
   *phi = enc.angle;   
   shmdt(shared_mem); 
   cout << "update ende" << endl;
   
}

int main( int argc, const char* argv[] ){
   int enc_Number;
   if( argc < 2 ){
      cout << "Bitte mindestens einen Parameter übergeben zur Auswahl des Encoders" << endl;
      return 1;  // mindestens ein Parameter muss übergeben werden
    }
   if (sscanf (argv[1], "%i", &enc_Number)!=1){
     cout << "Parameter konnte nicht gelesen werden" << endl;
     return 2;
   }
   cout << "Encoder Nr.: " << enc_Number << endl;

   wiringPiSetup();
   init( enc_Number );
   shared_mem_id = shmget(SMkey, SMsize, 0666);

   while(1){

      enc.input = digitalRead( enc.a ) << 1 | digitalRead( enc.b );       
      if (enc.input != enc.input_old){    // wenn Änderung stattgefunden hat
         enc.input_old = enc.input;       // Eingabe speichern für Abgleich    
         enc.state = Automat[enc.state].ai[enc.input]; // neuer Zustand wird aus dem Automaten ermittelt              
                  
         if( Automat[enc.state].outValue )
            enc.angle++;        
         else
            enc.angle--; 

         if( enc.angle >= 960 )
            enc.angle = 960 - enc.angle;
         if( enc.angle < 0 )   
            enc.angle = 960 + enc.angle;

         cout << "starte thread" << endl;
	 new thread( update );
         
      }
      usleep(10);
   }
}
