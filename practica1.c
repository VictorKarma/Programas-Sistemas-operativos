#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

void main(void)
{
	printf("ID del proceso: %d\n", (long)getpid());
	printf("ID del padre proceso: %d\n", (long)getppid());
	printf("ID del usuario propietario: %d\n", (long)getuid());
}
