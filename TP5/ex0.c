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

int counter=0; 


typedef struct __myarg_t{

	int incrementation;

}myarg_t;



void *firstthread(void * arg){

	myarg_t *op = (myarg_t*) arg;

	for(int i = 0 ; i < op->incrementation ; i++) {
		counter++;

	}
	

	return NULL;

}

int main(int argc , char * argv[]){

pthread_t t1,t2,t3;
int rc1,rc2,rc3;

myarg_t args;

args.incrementation = atoi(argv[1]);


rc1 = pthread_create( &t1, NULL , firstthread, &args );
assert(rc1 == 0);
rc2 = pthread_create( &t2, NULL , firstthread, &args );
assert(rc2 == 0);
rc3 = pthread_create( &t3, NULL , firstthread, &args );
assert(rc3 == 0);

pthread_join( t1, NULL);

pthread_join( t2,NULL);

pthread_join( t3, NULL);

printf(" valor esperado do contador %d \n", 3*args.incrementation );
printf("valor obtido no contador %d \n", counter );




}