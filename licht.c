/*
   überwacht, ob Gelenk im Ausgangszustand ist
   g++ lichtB.c -std=c++0x -o lichtB -pthread -lwiringPi
*/

#include "licht.h"
#include <wiringPi.h>
#include "shrd_mem.h"

char licht_b = 0;
char licht_c = 0;

void init(  ){
	pinMode ( PIN_licht_b , INPUT );
   pinMode ( PIN_licht_c , INPUT );
}

int main(){
   
   wiringPiSetup();
   init(  );
   shared_mem_id = shmget(SMkey, SMsize, 0666);

   char save_b, save_c;
   
   while(1){
   	if( licht_b != (save_b = digitalRead( PIN_licht_b )) ||
          licht_c != (save_c = digitalRead( PIN_licht_c ))  ){
             licht_b = save_b;
             licht_c = save_c;
             shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);  // Zugriff auf shared memory bekommen 
             shared_mem->licht_b = licht_b;
             shared_mem->licht_c = licht_c;
             shmdt(shared_mem);
      }
      usleep(1000);

   }
}