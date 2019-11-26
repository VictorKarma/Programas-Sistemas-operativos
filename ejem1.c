#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include<unistd.h>

int main()
{
	pid_t pid1,pid2;
	pid1=fork();
	if(pid1>0){
		pid2=fork();
		if(pid2>0){//Padre C
			int id,*ap,status,c[15],suma,i;
			suma=0;
			wait(&status);
			wait(&status);
			id=shmget(ftok(".",'&'),sizeof(c),IPC_CREAT);
			ap=shmat(id,0,0);
			for(i=0;i<15;i++){
				printf("ap %d: %d\n",i,*ap+i);
				suma+=*(ap+i);
			}
			shmdt(ap);
			shmctl(id,IPC_RMID,NULL);
			id=shmget(ftok(".",'%'),sizeof(int),IPC_CREAT);
			ap=shmat(id,0,0);
			*ap=suma;
		}
		if(pid2==0){//Hijo B
			int id,*ap,B[15],i;
			id=shmget(ftok(".",'&'),sizeof(B),IPC_CREAT);
			ap=shmat(id,0,0);
			for(i=1;i<=15;i+=2){
				//*(ap+i)=i;
				*(ap+i)=(100);
			}
		}
	}
	if(pid1==0){//Hijo A
		int id,*ap,B[15],i;
		id=shmget(ftok(".",'&'),sizeof(B),IPC_CREAT);
		ap=shmat(id,0,0);
		for(i=0;i<15;i+=2){
			//*(ap+i)=i;
			*(ap+i)=(100);
		}
	}
}
