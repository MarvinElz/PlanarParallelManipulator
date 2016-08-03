// g++ stift.c -std=c++0x -o stift -pthread -lwiringPi

#include "shrd_mem.h"
#include "stift.h"
#include <wiringPi.h>
#include <thread>
#include <unistd.h>  // usleep()

char pos = 0;

void init(){
   pinMode ( PIN_stift , OUTPUT );
}

void run(){
	while(1){
		digitslWrite( PIN_stift, 1 );
		if( pos )
		   usleep(1000);
		else
		   usleep(2000);
		digitslWrite( PIN_stift, 0 );   
		usleep(20000);
	}
}

int main( int argc, const char* argv[] ){
	
   wiringPiSetup();
   init(  );
   shared_mem_id = shmget(SMkey, SMsize, 0666);

   std::thread go(run);
   
   while(1){
   	shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
   	pos = shared_mem->UP;
   	shmdt(shared_mem);
   	usleep(100000);
   }

}