#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include<unistd.h>

void GeneraPares(int tuberia, int t1, int t2)
{
	int i=0;
	char testigo;
	/*i es el número par que se genera*/
	/*Se geenera el primer lugar el 0*/
	write(tuberia, &i, sizeof(const void));
	/*Sede el turno a p2*/
	write(t1, testigo, sizeof(const void));
	for(i=0; i < 2000; i=i+2)
	{
		/*Espera el turno*/
		read(t2, testigo, sizeof(void));
		/*Inserta el siguiente número par*/
		write(tuberia, &i, sizeof(const void));
		/*Cede el turnoa p2*/
		write(t1, &testigo, sizeof(const void));

	}
	return;
}

void GeneraImpares(int tuberia, int t1, int t2)
{
	int i=0;
	char testigo;
	/*i es el númeero impar que se ogenera*/
	for(i=1; i<2000; i=i+2)
	{
		/*Espera el turno */
		read(t1, &testigo, sizeof(void));
		/*Inserta el ssiguieente numero par*/
		write(tuberia, &i, sizeof(const void));
		/*Cede el turno al p1*/
		write(t2, &testigo, sizeof(const void));
	}
	return;
}

void ConsumeNumeros(int tuberia)
{
	int i;
	while(read(tuberia, &i, sizeof(int)) > 0)
	{
		/*Escribe el caracter*/
		printf("%d\n",i);
	}
	return;
}

int main ()
{
	pid_t pid1, pid2;
	/*Tuberia ocupada como sisstema dde comunicación*/
	/*Entre los tres procesos*/
	int tuberia[2];

	/*Tuberias utilizadas para sincronizar a los procesos p1 y p2*/
	int t1[2], t2[2];
	/*El proceso padre será el que cree la tuberia*/
	if (pipe(tuberia) < 0)
	{
		perror("No se puede crear la tuberia");
		exit(0);
	}
	if (pipe(t1) < 0)
	{
		perror("No se puede crear la tuberia");

		exit(0);
	}
	if(pipe(t2) < 0)
	{
		perror("No se puede crear la tuberia");
	}
	/*Se crea elproceso p1*/
	switch(pid1=fork())
	{
		case -1:
			perror("No se pued crear el proceso");
			/*Se ciierra la pipe*/
			close(tuberia[0]);
			close(tuberia[1]);
			close(t1[0]);
			close(t1[1]);
			close(t2[0]);
			close(t2[1]);
			exit(0);
		case 0: /*Proceso hijo proceso p1*/
			/*Cierra el descriptor de lecura de la pipe*/
			close(tuberia[0]);
			/*Este proceso lee de t1 y escribe en t2*/
			close(t1[1]);
			close(t2[0]);
			GeneraImpares(tuberia[1], t1[0], t2[1]);
			/*El  proceso acaba los descriptores*/
			close(tuberia[1]);
			close(t1[0]);
			close(t2[1]);
			break;
		default:
			/*El proceso padre crea ahora el proceso p2*/
			switch(pid2 = fork())
			{
				case -1:
					perror("Error al crear el proceso p2");
					/*Se ciierra la pipe*/
                        		close(tuberia[0]);
		                        close(tuberia[1]);
                		        close(t1[0]);
		                        close(t1[1]);
		                        close(t2[0]);
		                        close(t2[1]);
					/*Se mata el proceso anterior*/
					kill(pid1, SIGKILL);
					exit(0);
				case 0:/*Proceso hijo p2*/
					/*lee de la tuberia*/
					/*Cierra el descriptor de escritura*/
					close(tuberia[1]);
					/*no necesita t1 ni t2*/
					close(t1[0]);
                                        close(t1[1]);
                                        close(t2[0]);
                                        close(t2[1]);
					ConsumeNumeros(tuberia[0]);
					close(tuberia[0]);
					exit(0);
					break;
				default:/*Procesoo padre*/
					/*Escribe en la tuberia*/
					/*Cierra el descriptor de lectura*/
					close(tuberia[0]);
					/*Este proceso lee de t2*/
					/*y escribe en t1.Cierra lo que no necesita*/
					close(t1[0]);
					close(t2[1]);
					GeneraImpares(tuberia[1], t1[1], t2[0]);
					/*El proceso cierra los descriptores*/
					close(tuberia[1]);
					close(t1[1]);
					close(t2[0]);
			}
	}
}
