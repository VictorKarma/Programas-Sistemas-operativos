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
	int key, i, id_zone, *buffer;
   	/*LLave para memoria compartida */
	key = ftok(FILEKEY, KEY);
   	if (key == -1)
	{
		fprintf (stderr, "Error al crear llave \n");
      	return -1;
   	}

   	/* Se crea la memoria comartida*/
   	id_zone = shmget (key, sizeof(int)*MAXBUF, 0777 | IPC_CREAT);
   	if (id_zone == -1)
	{
      		fprintf (stderr, "Error al crear memoria compartida\n");
      		return -1;
   	}

   	printf ("ID de la zona de memoria compartida: %i\n", id_zone);
   	/* Declaracion de la memoria compartida */
   	buffer = shmat (id_zone, (char *)0, 0);
   	if (buffer == NULL)
	{
      		fprintf (stderr, "Error al reservar memoria compartida \n");
      		return -1;
   	}


	printf ("Puntero del buffer de la memoria compartida: %p\n", buffer);
   	/* Escribe los valores a la memoria */
   	for (i = 0; i < MAXBUF; i++)
	{
      		printf ("%i\n", buffer[i]);
	}
   	return 0;
}
