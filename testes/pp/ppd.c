/* ppd.c

d) Desenvolva um novo programa que, para além de fazer o
que é pedido nas alíneas anteriores, faça com que os 2 threads de
inicialização inicializem *mesmo* o vector partilhado, mas sem
tentarem evitar erros de competição ("race conditions").  A impressão
da informação já pedida na alínea anterior irá permitir ver o trabalho
que foi efectuado.  

*Nota:* aqui já deve ser possível observar que há erros de
competição, mesmo para um vector partilhado com um nº de elementos
relativamente pequeno! É óbvio, pois não houve esforço de
sincronização no acesso ao vector!

Exemplo de invocação:
     ./ppd 6000 4000
*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

vector_t vector;	// estrutura de dados a partilhar pelos threads

// a preencher com o seu código!

void *thread1(void*arg){

	printf("Thread %ld running\n", pthread_self());

	int X = 0,Y, Z;
	vector_t *op = (vector_t*) arg;
	Y = op->cnt[0];
	Z= &op;
	
	while(op->cnt[0] > 0 ){

		op->array[op->next]= X;
		op->cnt[0]--;
		op->next++;
		printf("Thread %d: cnt = %d, vp = %p\n", X, Y, Z );

	}
	

	print_vector(op);
	printf("\n");

	return NULL;
}

void *thread2(void*arg){


	printf("Thread %ld running\n", pthread_self());
	int X = 1,Y, Z;
	vector_t *op = (vector_t*) arg;
	Y = op->cnt[1];
	Z= &op;
	

	while(op->cnt[1] > 0 ){

		op->array[op->next]= X;
		op->cnt[1]--;
		op->next++;
		printf("Thread %d: cnt = %d, vp = %p\n", X, Y, Z );
	}

	

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

vector.next = 0;

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