#include <stdio.h>
#include <stdlib.h>
#include <linux/ipc.h>
#include <linux/msg.h>
 int main()
{
	int qid;
	key_t msgkey;
	struct mymsgbuf 
	{
		long mtype; /* Tipo de mensaje */
		int request; /* Numero de trabajo */
		double salary; /* Salario del empleado */
	} msg;
/* Generamos nuestra clave IPC */
	msgkey = ftok(".", ’m’);
/* Abrir/crear la cola */

	if(( qid = abrir_cola( msgkey)) == -1) 
	{
		perror("abrir_cola");
		exit(1);
	}
/* Preparar mensajes con datos arbitrarios */
	msg.mtype = 1; /* !El mensaje debe ser numero positivo! */
	msg.request = 1; /* Dato numero 1 */
	msg.salary = 1000.00; /* Dato numero 2 (!mi salario anual!) */
	if((enviar_msj( qid, &msg )) == -1) 
	{
		perror("enviar_msj");
		exit(1);
		int abrir_cola( key_t keyval )
		{
			int qid;
			if((qid = msgget( keyval, IPC_CREAT | 0660 )) == -1)
			{
				return(-1);
			}
			return(qid);
		}
	int enviar_msj( int qid, struct mymsgbuf *qbuf )
	{		
		int resultado, longitud;
		longitud = sizeof(struct mymsgbuf) - sizeof(long);
		if((resultado = msgsnd( qid, qbuf, length, 0)) == -1)
		{
			return(-1);
		}
		return(resultado);
	}
}
}

