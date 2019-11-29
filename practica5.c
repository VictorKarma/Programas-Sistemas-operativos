#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main()
 {
    char *home = NULL;
    home = getenv("HOME");
    if(home == NULL)
      {
        printf("HOME no se encuentra definida\n");
      }
    else
      {
	printf("El valor de HOME es: %s\n",home);
      }

 }
