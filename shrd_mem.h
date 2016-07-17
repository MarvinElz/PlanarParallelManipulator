#ifndef SHRD_MEM_H_
#define SHRD_MEM_H_

#include <sys/shm.h>		//Used for shared memory
#include <sys/ipc.h>


struct shared_mem_struct{
   int phi_b;          // Position Gelenk 1
   int phi_c;          // Position Gelenk 2
   int phi_b_soll;     // SollPosition Gelenk 1
   int phi_c_soll;     // SollPosition Gelenk 2
}typedef shared_mem_struct;

#define offset_phi_b ( 0 )
#define offset_phi_c ( sizeof( int ) )
#define offset_phi_b_soll ( 2 * sizeof(int) )
#define offset_phi_c_soll ( 3 * sizeof(int) )

int shared_mem_id;               // shared-memory key
shared_mem_struct *shared_mem;   // Pointer on shared_mem_struct

#define SMkey 58120526
#define SMsize sizeof(shared_mem_struct)

#endif