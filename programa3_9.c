#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main(int argc, char **argv)
{
    pid_t pid;
    char *argumentos[3];

    argumentos[0] = "ls";
    argumentos[1] = "-a";
    argumentos[2] = NULL;

    pid =fork();
    switch(pid)
    {
        case -1: /*error del forck() */
        exit(1);
        case 0: /* proceso hijo */
        execvp(argumentos[0],argumentos);
        perror("exec");
        break;
        default: /* padre */
        printf("procesos padre\n"); 
     
    }

}
