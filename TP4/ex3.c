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

	int pid,tid;
	pid = getpid();
	tid = pthread_self();
	int *output = malloc(sizeof(int));
	*output = *((int *) arg);

	printf(" O PID da %dª thread é : %d\n",*output, pid);
	printf(" O TID da %dª thread é : %d\n",*output, tid);

	

	return (void * )  output;
}



int main(int argc , char * argv[]){

	int NUMBER_OF_THREADS = atoi(argv[1]), i;

	pthread_t t[NUMBER_OF_THREADS];

	int rc[NUMBER_OF_THREADS], *output, main_pid;

		for( i= 1; i< NUMBER_OF_THREADS ; i++){

			int *arg = malloc(sizeof(*arg));

			*arg = i;

			rc[i] = pthread_create(&t[i], NULL, firstthread , arg );

			assert(rc[i] == 0 );

			pthread_join(t[i], (void **) &output);

			printf(" resultado thread %d: %d\n",i, *output);
			
		}




	main_pid = getpid();
	printf( " main pid é : %d\n", main_pid);



}
