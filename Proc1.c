#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h> /* shm*  */

#define FILEKEY "/bin/cat"
#define KEY 1300
#define MAXBUF 10



int main ()
{
	int key, i;
	int id_zone;
	int *buffer;
	char c;
	//LLava e para la memoria compartida
	key = ftok(FILEKEY, KEY);
	if (key == -1)
	{
		fprintf (stderr, "Error al crear la llave \n");
		return -1;
	}
	//Crea la memoria compartida
	id_zone = shmget (key, sizeof(int)*MAXBUF, 0777 | IPC_CREAT);
	if (id_zone == -1)
	{
		fprintf (stderr, "Error al crear memoria compartida\n");
	      	return -1;
   	}
	printf ("ID zone shared memory: %i\n", id_zone);
   	//Declarar memoria compartida
   	buffer = shmat (id_zone, (char *)0, 0);
   	if (buffer == NULL)
	{
	      	fprintf (stderr, "Error al reservar memoria compartida \n");
      		return -1;
	}
   	printf ("Puntero al buffer de la memoria compartida %p\n", buffer);
	for (i = 0; i < MAXBUF; i++)
	{
		buffer[i] = i;
	}
	c = getchar();
   	//libera la memoria compartida
	shmdt ((char *)buffer);
	shmctl (id_zone, IPC_RMID, (struct shmid_ds *)NULL);
   	return 0;
}
