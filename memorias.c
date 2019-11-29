#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define SEGSIZE 100

void writeshm(int shmid, char *segptr, char *text);
void readshm(int shmid, char *segptr);
void removeshm(int shmid);
void changemode(int shmid, char *mode);
void usage(void);
int main (int argc, char *argv[])
{
	key_t key;
	int shmid, cntr;
	char *segptr;

	if(argc == 1)
		usage();
	//Obtener clave IPC
	key = ftok(".",'S');

	//Abrir (crear si es necesario) el segmento de memoria compartida
	if((shmid = shmget(key, SEGSIZE, IPC_CREAT|IPC_EXCL|0666)) == -1)
	{
		printf("El segmento existe - abriendo como cliente\n");

		//El segmento existe - abrir como cliente
		if((shmid = shmget(key, SEGSIZE, 0)) == -1)
		{
			perror("shmget");
			exit(1);
		}
	}
	else
	{
		printf("Creando nuevo segmento\n");
	}
	//Ligar el proceso actual al segmento
	if((segptr = shmat(shmid, 0, 0)) == 0)
	{ 	
		perror("shmat");
		exit(1);
	}

	switch(tolower(argv[1][0]))
	{
		case 'e': writeshm(shmid, segptr, argv[2]);
			  usage();
			  break;
		case 'l': readshm(shmid, segptr);
			  usage();
			  break;
		case 'b': removeshm(shmid);
			  usage();
			  break;
		case 'm': changemode(shmid, argv[2]);
			  usage();
			  break;
		default:  usage();
	}
}
void writeshm(int shmid, char *segptr, char *text)
{
	strcpy(segptr, text);
	printf("Hecho...\n");
}
void readshm(int shmid, char *segptr)
{
	printf("Valor de segptr: %s\n", segptr);
}
void removeshm(int shmid)
{
	shmctl(shmid, IPC_RMID, 0);
	printf("Segmento marcado para borrado\n");
}
void changemode(int shmid, char *mode)
{
	struct shmid_ds myshmds;

	//Obtener valor actual de la estructura de datos interna
	shmctl(shmid, IPC_STAT, &myshmds);

	//Mostrar antiguos permisos
	printf("Antiguos permisos: %o\n", myshmds.shm_perm.mode);

	//Convertir y cargar el modo
	sscanf(mode, "%ho", &myshmds.shm_perm.mode);

	//Actualizar el modo
	shmctl(shmid, IPC_SET, &myshmds);

	printf("Nuevos permisos: %o\n", myshmds.shm_perm.mode);
}
void usage(void)
{
	fprintf(stderr, "shmtool - Utilidad para usar memoria compartida\n");
	fprintf(stderr, "\nUSAGE: shmtool (e)scribir <texto>\n");
	fprintf(stderr, "		  (l)eer\n");
	fprintf(stderr, "		  (b)orrar\n");
	fprintf(stderr, "		  (m)odo <modo en octal>\n");
	exit(1);
}
