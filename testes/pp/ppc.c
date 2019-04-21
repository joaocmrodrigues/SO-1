/* ppc.c

c) Desenvolva um novo programa, que além de fazer o que é pedido
nas alíneas anteriores, deverá fazer com que cada um dos threads
de inicialização invoque a função printf() do seguinte modo:

	printf ("Thread %d: cnt = %d, vp = %p\n", X, Y, Z);

onde X representa o identificador do thread (ou 0 ou 1), Y representa
o nº de elementos que o thread deverá inicializar, e Z o endereço da
estrutura de dados do tipo vector_t partilhada pelos threads de
inicialização.  Antes de terminar cada thread deverá ainda
invocar a função print_vector() já referida.

Nota: Cada thread deverá invocar esta instrução com um valor X diferente.

Exemplo de invocação:
     ./ppc 6000 4000
*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

vector_t vector;	// estrutura de dados a partilhar pelos threads

// a preencher com o seu código!

void *thread1(void*arg){

	int X = 0,Y, Z;
	vector_t *op = (vector_t*) arg;
	Y = op->cnt[0];
	Z= &op;
	printf("Thread %ld running\n", pthread_self());

	printf("Thread %d: cnt = %d, vp = %p\n", X, Y, Z );

	print_vector(op);
	printf("\n");

	return NULL;
}

void *thread2(void*arg){

	int X = 1,Y, Z;
	vector_t *op = (vector_t*) arg;
	Y = op->cnt[1];
	Z= &op;
	printf("Thread %ld running\n", pthread_self());

	printf("Thread %d: cnt = %d, vp = %p\n", X, Y, Z );

	print_vector(op);
	printf("\n");
	return NULL;
}



int main(int argc, char *argv[]) {
setbuf(stdout, NULL);

pthread_t t[2];

int  n1 , n2 ;

n1 = atoi(argv[1]);
n2 = atoi(argv[2]);

vector.len = (n1+n2);
vector.array = malloc(sizeof(int)*vector.len);

vector.next = vector.array[1];

//vector.lock = NULL;
vector.cnt[0] = n1;
vector.cnt[1] = n2;



pthread_create(&t[0], NULL , thread1 , &vector);

pthread_create(&t[1], NULL , thread2 , &vector);


pthread_join(t[0], NULL);
pthread_join(t[1], NULL);



// a preencher com o seu código!



// a preencher com o seu código!

print_vector(&vector);
printf("\n");
printf("Main thread exiting\n");

return 0;
}

// a preencher com o seu código!
