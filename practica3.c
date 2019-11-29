#include <sys/types.h>
#include <stdio.h>
#include<unistd.h>

int main()
{
	/*Declaración de variables para las funciones*/

	pid_t id_proceso; 
        pid_t id_padre;
	uid_t us_real;
	uid_t us_ef;
	gid_t team_real;
	gid_t team_ef;

	/*Llamado de las funciones*/
        id_proceso = getpid();
        id_padre   = getppid();
 	us_real = getuid();
        us_ef = getuid();
        team_real = getgid();
        team_ef = getgid();
       

printf("Identificador del proceso:%d\n",id_proceso);
printf("Indentificador del proceso padre:%d\n",id_padre);
printf("Indentificador del us_real:%d\n",us_real);
printf("Indentificador del us_ef:%d\n",us_ef);
printf("Indentificador del team_real:%d\n",team_real);
printf("Indentificador del team_ef:%d\n", team_ef);
}


