/*
    liefert aktuelle Position der Winkel an das Hauptprogramm
    ueber shared-memory
    Ablaufsteuerung über Zustandsautomaten
*/

#include "shrd_mem.h"
#include "encoder.h"
#include <wiringPi.h>

struct Zustand{		
	char outValue;
	char ai[4];
} typedef Zustand;

Zustand Automat[4] = {  {  1, { 0, 1, 2, 3 } },   // rechtsdrehung
						{  0, { 0, 1, 2, 3 } },   // linksdrehung
						{  1, { 1, 0, 3, 2 } },   // rechtsdrehung
						{  0, { 1, 0, 3, 2 } } }; // linksdrehung

char state = 0;
char eingabe;		// interpretiertes Einlesen [0..3]
char alteeingabe;   // wird benötigt für Haltepositionen, Ausgabe nur bei Änderung


int init(){
	pinMode ( enc1_a, INPUT );
	pinMode ( enc1_b, INPUT );
}

int main( int argc, const char* argv[] ){

   wiringPiSetup();
   shared_mem_id = shmget(SMkey, SMsize, 0666);

   while(1){

       eingabe = digitalRead( enc1_a ) << 1 | digitalRead( enc1_b );
       
   	  if (eingabe != alteeingabe){    // wenn Änderung stattgefunden hat
         alteeingabe = eingabe;       //      
         state = Automat[AktuellerZustand].ai[eingabe]; // neuer Zustand wird aus dem Automaten ermittelt      
          
         shared_mem = (shared_mem_struct*)shmat(shID, 0, 0);
         if( Automat[state].outValue )
            shared_mem->phi_b++;
         else
            shared_mem->phi_b--;
         shmdt(shared_mem);
      }
   }
}
