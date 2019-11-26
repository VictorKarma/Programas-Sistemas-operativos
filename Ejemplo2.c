#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
	int id, *ap;
	id=shmget(ftok(".",'%'),sizeof(int),IPC_CREAT);
	ap=shmat(id,0,0);
	printf("Suma: %d\n",*ap);
}
