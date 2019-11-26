#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h> /* shm*  */

#define FILEKEY "/bin/cat"
#define KEY 1300
//#define NUM 10
int NUM=0;
pid_t pidL, pidM;
//int num=10;
void manejador()
{
	printf("Recibi la señal");
	kill(getpid(),SIGKILL);
	kill(pidL,SIGKILL);
	kill(pidM,SIGKILL);
}


int main ()
{
	//estructura de la señal
	struct sigaction act;
	act.sa_handler = manejador;
	sigemptyset (&act.sa_mask);
	act.sa_flags=0;
	sigaction(SIGALRM,&act,NULL);
	alarm(3);
	//Declaracion de variables
	int fd[2];
	int key, i;
        int id_zone;
        int *buffer;
        char c;
	char a;
        pipe(fd);//Creacion de tuberia
	/*El proceso padre crea la memoria compartida para la sincronización de los procesos*/
        //LLava e para la memoria compartida
        key = ftok(FILEKEY, KEY);//crea la llave
        if (key == -1)//Si no s epude crear la llave
        {
                fprintf (stderr, "Error al crear la llave \n");//Despliega letrero
                return -1;
        }
        //Crea la memoria compartida
        id_zone = shmget (key, sizeof(int)*NUM, 0777 | IPC_CREAT);
        if (id_zone == -1)//Si no se pudo crear la memoria
        {
                fprintf (stderr, "Error al crear memoria compartida\n");//Despliega letrero
                return -1;
        }
        //printf ("ID zone shared memory: %i\n", id_zone);//Imprime el ID de la zona
        //Ata memoria compartida
        buffer = shmat (id_zone, (char *)0, 0);
        if (buffer == NULL)//Si no se puede atar la memoria
        {
                fprintf (stderr, "Error al reservar memoria compartida \n");//Imprime error
                return -1;
        }
        //printf ("Puntero al buffer de la memoria compartida %p\n", buffer);//Imprim el puntero
	//printf("Soy el prceso R \t Mi ID es: %d\n",getpid());
	pipe(fd);//Creacion de tuberia
	pidL = fork();//Cracion de proceso L
	if (pidL == 0)//Si se creo el proceso L
	{
		/*Crea memoria compartida para modificar variable compartida, incrementa variable*/
		//printf("Proceso hijo %d intentando entrar a memoria",getpid());
                int key, i, id_zone, *buffer;
                /*LLave para memoria compartida */
                key = ftok(FILEKEY, KEY);
                if (key == -1)
                {
                        fprintf (stderr, "Error al crear llave \n");
                	return -1;
                }
                /* Se crea la memoria comartida*/
                id_zone = shmget (key, sizeof(int)*NUM, 0777 | IPC_CREAT);
                if (id_zone == -1)
                {
                        fprintf (stderr, "Error al crear memoria compartida\n");
                        return -1;
                }
                //printf ("ID de la zona de memoria compartida: %i\n", id_zone);
                /* Declaracion de la memoria compartida */
                buffer = shmat (id_zone, (char *)0, 0);
                if (buffer == NULL)
                {
                        fprintf (stderr, "Error al reservar memoria compartida \n");
                        return -1;
                }

                //printf ("Puntero del buffer de la memoria compartida: %p\n", buffer);
		while(1)
		{
			//printf(" %d\t",getpid());
			NUM++;
			write(fd[1],&NUM,sizeof(int));
		}
	}
	pidM = fork();//Proceso de proceso M
	if (pidM == 0)
	{
		/*Crea memoria compartida para modificar variable compartida, decrementa variable*/
                //printf("Proceso hijo %d intentando entrar a memoria",getpid());
                int key, i, id_zone, *buffer;
                /*LLave para memoria compartida */
                key = ftok(FILEKEY, KEY);
                if (key == -1)
                {
                        fprintf (stderr, "Error al crear llave \n");
                        return -1;
                }
                /* Se crea la memoria comartida*/
                id_zone = shmget (key, sizeof(int)*NUM, 0777 | IPC_CREAT);
                if (id_zone == -1)
                {
                        fprintf (stderr, "Error al crear memoria compartida\n");
                        return -1;
                }
                //printf ("ID de la zona de memoria compartida: %i\n", id_zone);
                /* Declaracion de la memoria compartida */
                buffer = shmat (id_zone, (char *)0, 0);
                if (buffer == NULL)
                {
                        fprintf (stderr, "Error al reservar memoria compartida \n");
                        return -1;
                }
                //printf ("Puntero del buffer de la memoria compartida: %p\n", buffer);
		while(1)
		{
			//printf(" %d\t",getpid());
			NUM--;
			write(fd[1],&NUM,sizeof(int));
		}
	}
	while (1)//Imprime los datos a pantalla 
	{
		//printf("Soy el prceso padre \t Mi ID es: %d\n",getpid());
		read(fd[0],&NUM,sizeof(int));
		printf("%d\n",NUM);
		read(fd[0],&NUM,sizeof(int));
		printf("%d\n",NUM);
	}
	c = getchar();
        //libera la memoria compartida
        shmdt ((char *)buffer);
        shmctl (id_zone, IPC_RMID, (struct shmid_ds *)NULL);
        return 0;

}

