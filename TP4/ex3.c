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

 


void *firstthread(void * arg){

	int pid,tid, op;
	pid = getpid();
	tid = pthread_self();
	printf(" O PID da 1ª thread é : %d\n", pid);
	printf(" O TID da 1ª thread é : %d\n", tid);

	int *output = malloc(sizeof(int));
	//op = atoi(arg);
	*output = arg;

	return (void * )  output;
}



int main(int argc , char * argv[]){

	int NUMBER_OF_THREADS = atoi(argv[1]);

	pthread_t t[NUMBER_OF_THREADS];

	int rc[NUMBER_OF_THREADS], *output, main_pid;

		for(int i= 0 ; i< NUMBER_OF_THREADS ; i++){
			rc[i] = pthread_create(&t[i], NULL, firstthread , (void *)&i );
			assert(rc[i] == 0 );
			
			pthread_join(t[i], (void **) &output);

			printf(" resultado thread %d: %d\n",i, *output);
		}








main_pid = getpid();
printf( " main pid é : %d\n", main_pid);



}
