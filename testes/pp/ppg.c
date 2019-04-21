/* ppg.c

g) Desenvolva um novo programa que garanta que, em qualquer
instante da inicialização do vector partilhado, a diferença máxima (em
milhares) entre o nº de elementos inicializado por cada thread não
excede um dado valor. Isto permitirá um maior grau de "entremeação" -
e competição - na execução dos threads. Tal diferença máxima de
elementos inicializados será apresentada como um parâmetro adicional
na linha de comando. Por ex., com uma invocação na forma :

   ./ppg 5000 5000 1

o seu programa deverá criar 2 threads, o primeiro dos quais deverá
inicializar 5000 milhares de elementos com o valor 0 e o segundo com
5000 milhares com o valor 1, sendo que em qualquer instante o nº de
elementos inicializado por cada thread não pode diferir em mais de
1000.

O seu programa deverá usar semáforos ou variáveis de condição para
sincronizar correctamente os 2 threads de inicialização sem "busy
waiting."

Nota: Assuma que o programa é invocado sempre com argumentos
cujos valores são tais que o valor absoluto da diferença dos 2
primeiros argumentos não excede o valor do 3º argumento.

*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_cond_t var;
vector_t vector;	// estrutura de dados a partilhar pelos threads
chkr_arg_t ac;

int dif , count1=0, count2=0;


// a preencher com o seu código!

void *threadcheck(void*arg){

	chkr_arg_t *op = (chkr_arg_t*) arg;

	checker(op);
	return NULL;
}

void *thread1(void*arg){

	printf("Thread %ld running\n", pthread_self());

	int X = 0, Z;
	vector_t *op = (vector_t*) arg;
	Z= &op;
	
	while(op->cnt[0] > 0 ){

		pthread_mutex_lock(&op->lock);
		while((count1 - count2) > dif ) pthread_cond_wait(&var, &op->lock);
		op->array[op->next]= X;
		op->cnt[0]--;
		op->next++;
		count1++;
		printf("Thread %d: cnt = %d, vp = %p\n", X, op->cnt[0], Z );
		pthread_cond_signal(&var);
		pthread_mutex_unlock(&op->lock);
		printf("\n");

	}
	

	print_vector(op);
	printf("\n");
	pthread_cond_destroy(&var);

	return NULL;
}

void *thread2(void*arg){


	printf("Thread %ld running\n", pthread_self());
	int X = 1, Z;
	vector_t *op = (vector_t*) arg;
	Z= &op;
	

	while(op->cnt[1] > 0 ){
		pthread_mutex_lock(&op->lock);
		while((count2-count1 > dif)) pthread_cond_wait(&var, &op->lock);
		op->array[op->next]= X;
		op->cnt[1]--;
		op->next++;
		count2++;
		printf("Thread %d: cnt = %d, vp = %p\n", X, op->cnt[1], Z );
		pthread_cond_signal(&var);
		pthread_mutex_unlock(&op->lock);
	}

	

	print_vector(op);
	printf("\n");
	pthread_cond_destroy(&var);
	return NULL;
}



int main(int argc, char *argv[]) {
setbuf(stdout, NULL);

pthread_t t[2], tchecker;
pthread_mutex_init(&vector.lock, NULL);
pthread_cond_init(&var, NULL);

int  n1 , n2 ;

n1 = atoi(argv[1]);
n2 = atoi(argv[2]);
dif = atoi(argv[3])*1000;



vector.len = (n1+n2);
vector.array = malloc(sizeof(int)*vector.len);

vector.next = 0;

//vector.lock = NULL;
vector.cnt[0] = n1;
vector.cnt[1] = n2;


///inicializar ac 

ac.argc = argc ;
ac.argv = argv;
ac.vector = &vector;

pthread_create(&tchecker, NULL , threadcheck , &ac);


pthread_create(&t[0], NULL , thread1 , &vector);

pthread_create(&t[1], NULL , thread2 , &vector);


pthread_join(t[0], NULL);
pthread_join(t[1], NULL);


pthread_join(tchecker, NULL);

// a preencher com o seu código!



// a preencher com o seu código!

print_vector(&vector);
printf("\n");
pthread_mutex_destroy(&vector.lock);
printf("Main thread exiting\n");

return 0;
}