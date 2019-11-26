#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
pid_t pid;

pid = fork();
switch(pid){
case -1: /* error del fork() */
exit(-1);
case 0: /*Proceso hijo */
if(execvp(argv[1], &argv[1])< 0)
perror("exec");
default: /* padre */
printf("Proceso padre\n");
}
}
