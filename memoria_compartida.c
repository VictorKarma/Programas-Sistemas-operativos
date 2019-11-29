#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int get_sem_count(int sid);
void show_sem_usage(int sid);
int get_sem_count(int sid);
void dispval(int sid);


int main(int argc, char *argv[])
{
     key_t key;
     int semset_id;
      /* Obtener clave IPC unica */
      key = ftok(".", 's');
      /* Abrir (no crear!) el conjunto de semaforos */
      if((semset_id = semget(key, 1, 0666)) == -1)
  {
   printf("El conjunto no existe\n");
   exit(1);
  }
   show_sem_usage(semset_id);
   return(0);
}
void show_sem_usage(int sid)
{
  int cntr=0, maxsems, semval;
  maxsems = get_sem_count(sid);
  while(cntr < maxsems) 
  {
      semval = semctl(sid, cntr, GETVAL, 0);
      printf("Semaforo #%d: --> %d\n", cntr, semval);
      cntr++;
  }
  
}
   int get_sem_count(int sid)
{
   int rc;
   struct semid_ds mysemds;
   union semun semopts;
   /* Obtener valores de la estructura interna */
   semopts.buf = &mysemds;
   if((rc = semctl(sid, 0, IPC_STAT, semopts)) == -1) 
    {
	   
      perror("semctl");
      exit(1);
    }
    /* devolver numero de semaforos del conjunto */
    return(semopts.buf->sem_nsems);
	
}
    void dispval(int sid)
   {
      int semval;
      semval = semctl(sid, 0, GETVAL, 0);
      printf("semval vale %d\n", semval);
   }
   
