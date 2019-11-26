#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h> /* shm*  */
#include<unistd.h>


#define FILEKEY "/bin/cat"
#define KEY 1300
#define MAXBUF 10



int main ()
{
        int key, i;
        int id_zone;
        int *buffer;
        char c;
	pid_t pid1;
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
	pid1=fork();
	//Crea un hijo para entrar en memria compartida.
	if (pid1 == 0)
	{
		printf("Proceso hijo %d intentando entrar a memoria",getpid());
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
		//printf("Proceso hijo %d intentando entrar a memoria",getpid());
	}
        c = getchar();
        //libera la memoria compartida
        shmdt ((char *)buffer);
	shmctl (id_zone, IPC_RMID, (struct shmid_ds *)NULL);
        return 0;
}

