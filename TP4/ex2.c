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

#define NUMBER_OF_THREADS  3 


void *firstthread(void * arg){

	int pid,tid;
	pid = getpid();
	tid = pthread_self();
	printf(" O PID da 1ª thread é : %d\n", pid);
	printf(" O TID da 1ª thread é : %d\n", tid);

	int *output = malloc(sizeof(int));

	*output = 1;

	return (void * )  output;
}

void *secondthread(void * arg){


	int pid,tid;
	pid = getpid();
	tid = pthread_self();
	printf(" O PID da 2ª thread é : %d\n", pid);
	printf(" O TID da 2ª thread é : %d\n", tid);


int *output = malloc(sizeof(int));

	*output = 2;

	return (void * ) output;	
}

void *thirdthread(void * arg){


	int pid,tid;
	pid = getpid();
	tid = pthread_self();
	printf(" O PID da 3ª thread é : %d\n", pid);
	printf(" O TID da 3ª thread é : %d\n", tid);


int *output = malloc(sizeof(int));

	*output = 3;

	return (void * ) output ;	
}

int main(int argc , char * argv[]){

pthread_t t[NUMBER_OF_THREADS];

int rc[NUMBER_OF_THREADS], *output, main_pid;

rc[0] = pthread_create(&t[0], NULL, firstthread ,NULL);
assert(rc[0] == 0 );

rc[1] = pthread_create(&t[1], NULL, secondthread ,NULL);
assert(rc[1] == 0 );

rc[2] = pthread_create(&t[2], NULL,thirdthread ,NULL);
assert(rc[2] == 0 );



pthread_join(t[0], (void **) &output);
printf(" resultado thread 0: %d\n", *output);

pthread_join(t[1], (void **) &output);
printf(" resultado thread 1: %d\n", *output);

pthread_join(t[2], (void **) &output);
printf(" resultado thread 2: %d\n", *output);

main_pid = getpid();
printf( " main pid é : %d\n", main_pid);



}