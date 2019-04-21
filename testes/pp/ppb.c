/* ppb.c

b) Desenvolva um novo programa que, para além de fazer o
que é pedido em a) crie os 2 threads de inicialização. Cada
um destes threads deverá invocar a função printf() do seguinte
modo:

	printf ("Thread %d running\n", pthread_self());

O thread principal deverá esperar que cada um dos threads de inicialização
termine, após o que deverá imprimir:

	printf ("Main thread exiting\n");

Nota: Nesta alínea não precisa de passar qualquer argumento aos threads
de inicialização.

Exemplo de invocação:
     ./ppb 6000 4000
*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

vector_t vector;	// estrutura de dados a partilhar pelos threads

// a preencher com o seu código!


void *mythread(void*arg){

	printf("Thread %ld running\n", pthread_self());

	return NULL;
}

int main(int argc, char *argv[]) {
setbuf(stdout, NULL);

pthread_t t[2];

long int n1 , n2 ;

n1 = atoi(argv[1]);
n2 = atoi(argv[2]);

vector.len = (n1+n2);
vector.array = malloc(sizeof(int)*vector.len);

vector.next = vector.array[1];

//vector.lock = NULL;

for(int i = 0 ; i < 2 ; i++){
	vector.cnt[i]= 0;
}

for(int j = 0 ; j < 2 ; j++){

	pthread_create(&t[j], NULL , mythread , NULL);

	pthread_join(t[j], NULL);

}

// a preencher com o seu código!

printf("Main thread exiting\n");

print_vector(&vector);
return 0;
}

// a preencher com o seu código!
