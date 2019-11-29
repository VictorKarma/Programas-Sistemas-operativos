#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main()
{
  pid_t pid;
  pid = fork();
  switch(pid)
  {
    case -1: /*Error del fork*/
             perror("fork");
             break;
    
    case  0: /*proceso hijo*/
             printf("Proceso %d: padre = %d\n",getpid(),getppid());
             break;
    
    default:  /*padre*/
             printf("proceso %d: padre = %d\n",getpid(),getppid());
  }

}

