#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

#define t_SIZE 100

int main(int argc,char *argv[])
{
  int shmid;
  char aux[100];	
  key_t key; // biblioteca <sys/types.h>
  char *shm;
  char *s;
  key = 9876;
  shmid = shmget(key,t_SIZE,0);//ipc(sys/ipc) && // sys/shm // retur 1 OK ou erro
  if(shmid<0){
    perror("shmget");
    exit(1);
  }
  shm = shmat(shmid,NULL,0);
  if(shm == (char*) -1){
    perror("shmat");
    exit(1);
  }
  scanf("%[^\n]s",aux);

  
  memcpy(shm, aux,100);
 

  return 0;
}
