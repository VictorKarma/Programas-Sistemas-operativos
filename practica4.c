#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

extern char*environ;
void main(int argc,char*argv)
{
	int i;
	printf("Lista de variables de entorno de %s/n",argv[0]);

	for(i=0; environ[i]!=' ';i++)
	{
		printf("environ[%d]=%s\n",i,environ[i]);
	}
}
