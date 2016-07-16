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

Zustand Automat[4] = {  
        {  1, { 0, 1, 2, 3 } },   // rechtsdrehung
				{  0, { 0, 1, 2, 3 } },   // linksdrehung
				{  1, { 1, 0, 3, 2 } },   // rechtsdrehung
				{  0, { 1, 0, 3, 2 } } }; // linksdrehung

char Enc1_state = 0;
char Enc1_input;		// interpretiertes Einlesen [0..3]
char Enc1_input_old;   // wird benötigt für Haltepositionen, Ausgabe nur bei Änderung

char Enc2_state = 0;
char Enc2_input;    // interpretiertes Einlesen [0..3]
char Enc2_input_old;   // wird benötigt für Haltepositionen, Ausgabe nur bei Änderung


int init(){
	pinMode ( enc1_a, INPUT );
	pinMode ( enc1_b, INPUT );
  pinMode ( enc2_a, INPUT );
  pinMode ( enc2_b, INPUT );
}

int main( int argc, const char* argv[] ){

   wiringPiSetup();
   shared_mem_id = shmget(SMkey, SMsize, 0666);

   while(1){

      Enc1_input = digitalRead( enc1_a ) << 1 | digitalRead( enc1_b );       
      if (Enc1_input != Enc1_input_old){    // wenn Änderung stattgefunden hat
         Enc1_input_old = Enc1_input;       // Eingabe speichern für Abgleich    
         Enc1_state = Automat[Enc1_state].ai[Enc1_input]; // neuer Zustand wird aus dem Automaten ermittelt      
          
         shared_mem = (shared_mem_struct*)shmat(shID, 0, 0);  // Zugriff auf shared memory bekommen
         if( Automat[Enc1_state].outValue )
            shared_mem->phi_b++;
         else
            shared_mem->phi_b--;
         shmdt(shared_mem);
      }


      Enc2_input = digitalRead( enc2_a ) << 1 | digitalRead( enc2_b );       
      if (Enc2_input != Enc2_input_old){    // wenn Änderung stattgefunden hat
         Enc2_input_old = Enc2_input;       // Eingabe speichern für Abgleich    
         Enc2_state = Automat[Enc2_state].ai[Enc2_input]; // neuer Zustand wird aus dem Automaten ermittelt      
          
         shared_mem = (shared_mem_struct*)shmat(shID, 0, 0);  // Zugriff auf shared memory bekommen
         if( Automat[Enc2_state].outValue )
            shared_mem->phi_c++;
         else
            shared_mem->phi_c--;
         shmdt(shared_mem);
      }
      


   }
}
