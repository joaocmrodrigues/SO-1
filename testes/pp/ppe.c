/* ppe.c
e) Desenvolva um novo programa que, além de fazer o que é
pedido nas alíneas anteriores, cria um thread de verificação, i.e. que
executa a função checker() declarada em util.h. O argumento
desta função deve ser um apontador para uma variável do tipo
chkr_arg_t definida também em util.h, e aqui reproduzida:

typedef struct {
    int argc;          // to be initialized with argc of main()
    char **argv;       // to be initializedwith argv of main()
    vector_t *pvector; // to be initialized with pointer to the shared structure
} chkr_arg_t;

O thread de verificação deve ser criado antes dos threads de
inicialização e esperado pelo thread principal apenas depois daqueles
terem terminado.  

*Nota:* aqui também ainda devem ser patentes
os erros de competição, mesmo para um vector partilhado com um nº de
elementos relativamente pequeno, pois ainda pois não houve esforço de
sincronização no acesso ao vector!

Exemplo de invocação:
     ./ppe 6000 4000
*/


#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

vector_t vector;	// estrutura de dados a partilhar pelos threads
chkr_arg_t ac;

// a preencher com o seu código!

void *threadcheck(void*arg){

	chkr_arg_t *op = (chkr_arg_t*) arg;

	checker(op);
	return NULL;
}

void *thread1(void*arg){

	printf("Thread %ld running\n", pthread_self());

	int X = 0,Y, Z;
	vector_t *op = (vector_t*) arg;
	Z= &op;
	
	while(op->cnt[0] > 0 ){

		op->array[op->next]= X;
		op->cnt[0]--;
		op->next++;
		printf("Thread %d: cnt = %d, vp = %p\n", X, op->cnt[0], Z );
		printf("\n");

	}
	

	print_vector(op);
	printf("\n");

	return NULL;
}

void *thread2(void*arg){


	printf("Thread %ld running\n", pthread_self());
	int X = 1,Y, Z;
	vector_t *op = (vector_t*) arg;
	Z= &op;
	

	while(op->cnt[1] > 0 ){

		op->array[op->next]= X;
		op->cnt[1]--;
		op->next++;
		printf("Thread %d: cnt = %d, vp = %p\n", X, op->cnt[1], Z );
	}

	

	print_vector(op);
	printf("\n");
	return NULL;
}



int main(int argc, char *argv[]) {
setbuf(stdout, NULL);

pthread_t t[2], tchecker;

int  n1 , n2 ;

n1 = atoi(argv[1]);
n2 = atoi(argv[2]);

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
printf("Main thread exiting\n");

return 0;
}