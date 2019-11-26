#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

 int main()
{
pid_t pid;
int status;

pid =  fork();
switch(pid){
case -1: /* error del fork() */
exit(-1);
case 0: /* proceso hijo */
execlp("ls","ls","-1",NULL);
perror("exec");
break;
default: /* padre */
printf("Proceso padre\n");
}
}


