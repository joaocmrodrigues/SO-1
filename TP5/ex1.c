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
#include "tfun.h"

#define T_NUMBER 3 

pthread_mutex_t mut ; 


void *counter(void *arg){
	pthread_mutex_lock(&mut);
	targ_t *op  = (targ_t*)arg;
	tfun(op);
	pthread_mutex_unlock(&mut);
	return NULL;
}


int main(int argc , char *argv[]){

pthread_mutex_init(&mut, NULL);

pthread_t t[T_NUMBER];
int rc[T_NUMBER];

targ_t fun[T_NUMBER];

long int  *shared_counter =0;


for(int i= 0 ; i< T_NUMBER; i++){
	rc[i] = pthread_create(&t[i], NULL, counter , &fun[i]);
	fun[i].n= atoi(argv[1]);
	fun[i].id = t[i];
	fun[i].cnt = shared_counter;


	pthread_join(t[i],NULL);
}

pthread_mutex_destroy(&mut);

}