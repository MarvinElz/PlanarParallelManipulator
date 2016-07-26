#ifndef SHRD_MEM_H_
#define SHRD_MEM_H_

#include <sys/shm.h>		//Used for shared memory
#include <sys/ipc.h>


struct shared_mem_struct{
   int phi_b;          // Position Gelenk 1
   int phi_c;          // Position Gelenk 2
   int phi_b_soll;     // SollPosition Gelenk 1
   int phi_c_soll;     // SollPosition Gelenk 2
   char licht_b;       // Lichtschrankensensor Gelenk b
   char licht_c;       // Lichtschrankensensor Gelenk c
}typedef shared_mem_struct;




#define SMkey 58120526
#define SMsize sizeof(shared_mem_struct)

#endif
