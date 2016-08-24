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
  key_t key; // biblioteca <sys/types.h>
  char *shm;
  int size;
  struct shmid_ds buffer;
  char *s;
  key = 9876;
  shmid = shmget(key,t_SIZE,IPC_CREAT | 0666);//ipc(sys/ipc) && // sys/shm // retur 1 OK ou erro
  if(shmid<0){ 
    perror("shmget");
    exit(1);
  }
  shm = shmat(shmid,NULL,0);
  if(shm == (char*) -1){
    perror("shmat");
    exit(1);
  }
  
  memcpy(shm, "hello World",100);
  s = shm;
  
  s += 11;
  *s = 0;
  while (*shm != '*'){ sleep(1);}
  printf("Programa Finalizado com Sucesso\n");
 shmctl(shmid,IPC_RMID,0);
	
  return 0;
}
