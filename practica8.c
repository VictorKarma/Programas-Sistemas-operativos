#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
int main()
{
 pid_t pid;
 int i,n=10;
 for(i=0;i<n;i++)
  {
    pid = fork();
    if(pid == 0)
    {
      break;
    }
   printf("El padre del proceso %d es %d\n",getpid,getppid());
  }

}
