// Haupt-Steuerprogramm des Planaren-Parallelen-Manipulators
// aenderung
// g++ main.c -std=c++0x -o main -pthread 

#include "shrd_mem.h"
#include <unistd.h>  // usleep()
#include <iostream>

using namespace std;

int main(){
  shared_mem_id = shmget(SMkey, SMsize, IPC_CREAT | 0666);
  shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0); 
  shared_mem->phi_b = 0;
  shared_mem->phi_c = 0;
  shared_mem->phi_b_soll = 0;
  shared_mem->phi_c_soll = 0;

  while(1){
     shared_mem = (shared_mem_struct*)shmat(shared_mem_id, 0, 0);
     cout << "phi_b: " << shared_mem->phi_b << "  , phi_c: " << shared_mem->phi_c << endl;     
     shmdt(shared_mem);
     usleep(1000000);     
  }

  return 0;
}
