/*
    liefert aktuelle Position der Winkel an das Hauptprogramm
    ueber shared-memory
    Ablaufsteuerung über Zustandsautomaten
    g++ encoder.c -std=c++0x -o encoder -pthread -lwiringPi
    sudo ./encoder
    sudo ./encoder -A
    sudo ./encoder -B
*/

#include "shrd_mem.h"
#include "encoder.h"
#include <stddef.h>	// for offsetof()
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

int enc_a;
int enc_b;
int offset_phi_ist;		// Offset vom Pointer auf shared mem zu phi_ist

int init( int encNr ){
   if( encNr == 1 ){
      enc_a = enc1_a;
      enc_b = enc1_b;
      offset_phi_ist = offsetof( shared_mem_struct, phi_b );
   }else if( encNr == 2 ){
      enc_a = enc2_a;
      enc_b = enc2_b;
      offset_phi_ist = offsetof( shared_mem_struct, phi_c );
   }else{
      cout << "motNr out of range: [1,2]" << endl;
      return 0;
   }

   enc = { 0, 0, 0, 0, 0};  
   pinMode ( enc_a, INPUT );
   pinMode ( enc_b, INPUT );
   return 1;  
}

void update(){
   int* phi_ist;
   
   while(1){
      if( enc.angle != enc.angle_old ){
         shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);  // Zugriff auf shared memory bekommen
         phi_ist  = (int *)( (char*)shared_mem + offset_phi_ist );

         if( enc.angle_old != *phi_ist )  // änderung von außen
            enc.angle = *phi_ist;
         else 
            *phi_ist = enc.angle;  
         shmdt(shared_mem); 
         enc.angle_old = enc.angle;
      }
   usleep(10);
   }
   
}

int main( int argc, const char* argv[] ){
   int encNr = 0; // 1:A, 2:B

   if( argc != 2 ){
      cout << "Keinen Encoderparameter übergeben: nutze Encoder A" << endl;
      encNr = 1;
   }
   if( argc == 2 ){
      if( argv[1][1] == 'A' ){
          cout << "Nutze Encoder A" << endl;
          encNr = 1;
      }else
      if( argv[1][1] == 'B' ){
          cout << "Nutze Encoder B" << endl;
          encNr = 2;
      }else
      {
         cout << argv[1][1] << " ist kein richtiger Parameter ('A' / 'B')" << endl;
         cout << "Nutze Encoder A" << endl;
         encNr = 1;
      }   
   }   




   wiringPiSetup();
   if( !init( encNr ) ){
      cout << "Fehler während init()" << endl;
      return 1;
   }
   shared_mem_id = shmget(SMkey, SMsize, 0666);

   new thread( update );

   while(1){

      enc.input = digitalRead( enc_a ) << 1 | digitalRead( enc_b );       
      
      if (enc.input != enc.input_old){    // wenn Änderung stattgefunden hat
         enc.input_old = enc.input;       // Eingabe speichern für Abgleich   
         //cout << (int)enc.input << endl; 
         enc.state = Automat[enc.state].ai[enc.input]; // neuer Zustand wird aus dem Automaten ermittelt              
                  
         if( Automat[enc.state].outValue )
            enc.angle++;        
         else
            enc.angle--; 
/*
         if( enc.angle >= 960 )
            enc.angle = 960 - enc.angle;
         if( enc.angle < 0 )   
            enc.angle = 960 + enc.angle;
*/
	 
         
      }
      usleep(10);
   }
}
