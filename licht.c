/*
   überwacht, ob Gelenk im Ausgangszustand ist
   g++ licht.c -std=c++0x -o licht -pthread -lwiringPi
*/

#include "licht.h"
#include <wiringPi.h>
#include "shrd_mem.h"

struct LICHT{
	char state;         // aktuelle Zustand [0..1]  
	int  Pin_input;     // Input-Pin des Fototransistors
	int offset_licht;   // offset zum Pointer auf den shared memory
} typedef licht;

void init( int number ){
	
}

int main(){
   int licht_Number;
   if( argc < 2 ){
      cout << "Bitte mindestens einen Parameter übergeben zur Auswahl des Encoders" << endl;
      return 1;  // mindestens ein Parameter muss übergeben werden
    }
   if (sscanf (argv[1], "%i", &licht_Number)!=1){
     cout << "Parameter konnte nicht gelesen werden" << endl;
     return 2;
   }
   cout << "Licht Nr.: " << licht_Number << endl;


   while(1){
   	
   }
}