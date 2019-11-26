#include <sys/types.h> 
#include <stdio.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <sys/shm.h>
#define key 1555
#define key2 1553

void proce(int i,int proceso[],int llegada[],int b[],int rci[],int rcd[],int *turno,int *suma);

int main(int argc, char * argv[]) {  

   int pid1, pid2, pid3,pid4,estado; 
   int p1_finalizado = 0, p2_finalizado = 0, p3_finalizado = 0, p4_finalizado = 0; 
   int proceso[4];
   int llegada[4];
   int rci[4],rcd[4];
   int opc;
   int b[4];
   int t1=0;
   int id,id2;
   int *suma=NULL;
   int *turno=NULL;
	b[0]=0;b[1]=0;b[2]=0;b[3]=0;
	id=shmget(key,sizeof(int),IPC_CREAT|SHM_R|SHM_W); //se crea una memoria compartida para los turnos
	if (id == -1)//Verifica si se creo la memoria
	{
		perror("shmget:");
		exit(-1);
	}
	turno= (int *) shmat (id, NULL, 0);//Ata segmento de memoria
	(*turno)=0;
	id2=shmget(key2,sizeof(int),IPC_CREAT|SHM_R|SHM_W); //se crea una memoria compartida para modificar region critica
	if (id2 == -1)//Verifica si se creo la memoria 
	{
		perror("shmget:");
		exit(-1);
	}
	suma= (int *) shmat (id2, NULL, 0);//Ata segmento d memoria
	(*suma)=0;
	int i;
	for(i=0; i<4; i++)
	{
  		printf("Tiempo para proceso %d: ",i+1);  //se llenan los procesos con tiempo, region y duracion
		scanf("%d",&proceso[i]);
		printf("Region critica\n1)Si\n2)No\n"); //Pregunta si tiene región critica
		scanf("%d",&opc);
		if(opc==1)//Pide datos de la region
		{
			llegada[i]=t1;
			do//Pide datos de la region para los procesos que la tienen
			{
				printf("En que tiempo inicia\n");
				scanf("%d",&rci[i]);
			}while(rci[i]>proceso[i] && rci[i]<0);
			do//Pide dato  de la duración para los procesos que tienen region critica
			{
				printf("Duracion\n");
				scanf("%d",&rcd[i]);
			}while(rcd[i]<0);
			t1++;
		}
		else//Para los procesos que no tienen region critica
		{
			rci[i]=-1;
			llegada[i]=-1;
		}
	 }

	//Empiezan a ejecutarse los procesos
   	pid1=fork();
   	/* Este es el proceso 4 */
   	if (pid1 == 0)
	{
		while(proceso[3]!=0)   //mientras el tiempo del proceso sea diferente de 0
      		{
  			printf("Proceso 4\n");
			proce(3,proceso,llegada,b,rci,rcd,turno,suma);
		}
	      	puts("Proceso #4 finalizado.\n");
      		exit (0);
   	}
   	pid2=fork();
   	/* Este es el proceso #3 */
   	if (pid2 == 0)
	{
 		while(proceso[2]!=0)  // mientras el tiempo del proceso sea diferente de 0
      		{
			printf("Proceso 3\n");
  		 	proce(2,proceso,llegada,b,rci,rcd,turno,suma);
	  	}
      		puts("Proceso #3 finalizado.\n");
      		exit (0);
   	}
   	pid3=fork();
   	/* Este es el proceso #2 */
   	if (pid3 == 0)
	{
 		while(proceso[1]!=0)
      		{
			printf("Proceso 2\n");
		 	proce(1,proceso,llegada,b,rci,rcd,turno,suma);
		}
      		puts("Proceso #2 finalizado.\n");
	      	exit (0);
   	}
   	pid4=fork();
   	/* Este es el proceso #1 */
   	if (pid4 == 0)
	{
 		while(proceso[0]!=0)
      		{
			printf("Proceso 1\n");
		 	proce(0,proceso,llegada,b,rci,rcd,turno,suma);
		}
      		puts("Proceso #1 finalizado.\n");
      		exit (0);
   	}
   	if ((pid1 < 0) || (pid2 < 0) || (pid3 < 0) || (pid4 < 0))
	{ // se verifica que se hayan creado bien los procesos
      		printf("No creados...\n");
      		exit (1);
   	}
   	if ((pid1 > 0) && (pid2 > 0) && (pid3 > 0) && (pid4 > 0))
	{  // si los procesos han sido creados bien
      		while((!p1_finalizado) || (!p2_finalizado) || (!p3_finalizado) || (!p4_finalizado))
		{
         		int pid;
         		//se espera informacion de los procesos
         		pid = wait(&estado);
         		//se verifica que proceso ha finalizado y se marca
         		if (pid == pid1)
            			p1_finalizado = 1;
         		if (pid == pid2)
            			p2_finalizado = 1;
         		if (pid == pid3)
            			p3_finalizado = 1;
         		if (pid == pid4)
            			p4_finalizado = 1;
     		}
      //Se imprime que han terminado los procesos asi como la region critica
      puts("Procesos terminados.\n");
      printf("%d",*suma);
   }
}

void proce(int i,int proceso[],int llegada[],int b[],int rci[],int rcd[],int *turno,int *suma)
{
	if(rci[i]==proceso[i] && proceso[i]!=0 && b[i]!=1 && rci[i]!=-1)  //se verifica el tiempo de la region con
									 //el tiempo del proceso
	{
		printf("Intentando entrar a region critica\n");
		if(*turno==llegada[i])
		{// se verifica el turno
			printf("En region critica\n");
			printf("Tiempo restante region critica: %d\n",rcd[i]);  
			rcd[i]=rcd[i]-1;
			*suma=*suma+1;   //se modifica el valor de la region critica
			sleep(1);
			if(rcd[i]==0)  // cuando acabe el tiempo de la region se incrementa turno
			{
				printf("Proceso %d\n",i+1);
				printf("Saliendo de la region critica\n");
				proceso[i]--;  // se resta tiempo al proceso
				b[i]=1;
				*turno=*turno+1;  // se incrementa turno
				printf("Incrementando turno: %d\n",*turno);
				sleep(1);
			}
		}
		else //Si no desocupa región critica
		{
			printf("Memoria ocupada\n");
			printf("Lugar: %d\n",llegada[i]);
			sleep(1);
			}
		}
		else
		{
			if(b[i]==1)  // se verifica si el proceso ya ejecuto la region critica
			{
				printf("Tiempo: %d\n",proceso[i]);
				proceso[i]--;  // se resta tiempo al proceso
				printf("Este proceso ya ejecuto su region critica\n");
				sleep(1);
			}
			else
			{
				printf("Tiempo: %d\n",proceso[i]);
				proceso[i]--;  // se resta tiempo al proceso
				sleep(1);
			}
		}
}
