#include <sys/types.h>
#include <stdio.h>

int main()
{
	pid_t id_proceso;
        pid_t id_padre;

        id_proceso = getpid();
        id_padre   = getppid();

printf("Identificador del proceso:%d\n",id_proceso);
printf("Indetificador del proceso padre:%d\n",id_padre);
}
