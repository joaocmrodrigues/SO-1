
///first thread program

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>



typedef struct __myarg_t{
	int a;
	int b;
} myarg_t;



void *sum(void * arg){
	int *op;
	op = arg;
	int *soma1 = malloc(sizeof(int));
	*soma1 = op[0]+op[1];
	

	return (void *)soma1;
}

void *sub(void * arg){
	int *op;
	op = arg;
	int *subtracao1 = malloc(sizeof(int));
	*subtracao1 = op[0]-op[1];

	return (void *)subtracao1;
}

void *mult(void * arg){
	myarg_t *op = (myarg_t *) arg;
	int *multiplicacao1 = malloc(sizeof(int));
	*multiplicacao1 = (op->a)*(op->b);
	

	return (void *)multiplicacao1;
}

void *division(void * arg){
	myarg_t *op = (myarg_t *) arg;
	float *divisao1 = malloc(sizeof(float));
	*divisao1 = (float)(op->a)/(float)(op->b);
	

	return (void *)divisao1;
}

int main( int argc , char * argv[] , char *envp[]){

pthread_t t1,t2,t3,t4;
int rc1,rc2,rc3,rc4;

int myargs1[2];

myargs1[0] = atoi(argv[1]);
myargs1[1] = atoi(argv[2]);

myarg_t args;
args.a = atoi(argv[1]);
args.b = atoi(argv[2]);

int *v;
float *d;
rc1 = pthread_create(&t1, NULL , sum , myargs1  );
assert(rc1 == 0);
rc2 = pthread_create(&t2, NULL , sub , myargs1 );
assert(rc2 == 0);
rc3 = pthread_create(&t3, NULL , mult , &args  );
assert(rc3 == 0);
rc4 = pthread_create(&t4, NULL , division , &args  );
assert(rc4 == 0);

pthread_join(t1, (void **)&v );
printf(" O valor da soma é : %d\n", *v );

pthread_join(t2, (void **)&v);
printf(" O valor da subtração é : %d\n", *v);

pthread_join(t3, (void **)&v);
printf(" O valor da multiplicação é : %d\n", *v );

pthread_join(t4, (void **)&d);
printf(" O valor da divisão é : %f\n", *d);





}