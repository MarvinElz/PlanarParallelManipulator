/*
    liefert aktuelle Position der Winkel an das Hauptprogramm
    ueber shared-memory
    Ablaufsteuerung über Zustandsautomaten
*/

#include "shrd_mem.h"
#include "encoder.h"
#include <stdio>
#include <wiringPi.h>
#include <thread>

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
} typedef encoder;

encoder enc;


int init(int enc_Number){
  if( enc_Number == 1 )  
     enc = { 0, 0, 0, enc1_a, enc1_b, 0, 1};
  if( enc_Number == 2 )   
     enc = { 0, 0, 0, enc2_a, enc2_b, 0, 2 };
	pinMode ( enc.a, INPUT );
	pinMode ( enc.b, INPUT );
  
}

void update(){
   shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);  // Zugriff auf shared memory bekommen
   if( enc.number == 1 ){  // Encoder Nummer 1
      if( shared_mem->phi_b == 0 )          
         enc.angle = 0;     // Winiel wurde zurückgesetzt
      else
         shared_mem->phi_b = enc.angle;
   }
   if( enc.number == 2 ){  // Encoder Nummer 2
     if( shared_mem->phi_c == 0 )          
         enc.angle = 0;     // Winiel wurde zurückgesetzt
      else
         shared_mem->phi_c = enc.angle;
   }
   shmdt(shared_mem); 
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
            
         std::thread t1( update );          
         // TODO: call thread  
      }
   }
}
