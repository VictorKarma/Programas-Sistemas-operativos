#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}


struct TNodo
{
	int prioridad;
	char nombre[10];
	int tiempo;
	struct TNodo *izq;
	struct TNodo *der;
};

int main()
{
	struct TNodo *nodo, *p, *q, *nuevo, *cabecera;
	int n, i, prioridad, nombre, tiempo;
	printf("Progrma que crea procesos\n\n");
	
	cabecera = malloc(sizeof(struct TNodo));
	cabecera->prioridad =0;
	cabecera->nombre[i]=' ';
	cabecera->tiempo= 0;
	cabecera->izq=NULL;
	cabecera->der=NULL;
	
	do
	{
		p=malloc(sizeof(struct TNodo));
		printf("Deme la prioridad: ");
		scanf("%d", &p->prioridad);
		printf("Nombre del proceso ");
		scanf("%s", &p->nombre);
		printf(" Tiempo: ");
		scanf("%d", &p->tiempo);
		
		if(cabecera->der==NULL)
		{	
			p->der=NULL;
			p->izq=cabecera;
			cabecera->der=p;
		}
		else
		{
			q=cabecera;
			//p->prioridad=prioridad;
			while((((q->der)!=NULL) && ((p->prioridad > (q->der)->prioridad))))
				q=q->der;

			if (q->der==NULL)
			{
				q->der=p;
				p->der=NULL;
				p->izq=q;	
			}			
			else
			{
				p->der=q->der;
				q->der=p;
				p->izq=q;
				p->der->izq=p;
		    }
		}
		printf("agregar otro proceso: [0-NO] [1- SI]:  ");
		scanf("%d", &n);
		printf("\n");
	}while(n!=0);
	
		while(p->der!=NULL)
		p=p->der;
		
		while(p)
		{
		    printf("Nombre %s\n", p->nombre);
			printf("Tiempo %d\n", p->tiempo);
			printf("El prioridad fue %d\n",p->prioridad); 
			for(i=0;i<=p->tiempo;i++)
			{
			printf("Tiempo de ejecucion: %d...\n", i);
			delay(1000);
			}
			p=p->izq;
		}
	}
