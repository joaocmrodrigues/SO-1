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

#define t_loop 50000000 // 50M
#define reader_print 1000000 // 1M


long int m,n;
pthread_mutex_t mut;
pthread_cond_t var;

int r_flag = 0, w_flag =0 ;


void *reader(void*arg){
	long int  count =0, m_read, n_read;
	int j = 1;
	while(count < t_loop){

		pthread_mutex_lock(&mut);
		while( w_flag == 1) pthread_cond_wait(&var, &mut);
		r_flag = 1;
		m_read = m;
		n_read = n;
		r_flag = 0 ;

		pthread_cond_signal(&var);
		pthread_mutex_unlock(&mut);




		if(count == (reader_print *j) ){
			printf("o valor de m é: %ld ; e o valor de n é: %ld\n", m_read, n_read );
			j++;
		}


		count++;
	}
	return NULL;
}


void *writer(void*arg){
	int count = 0; 

	while(count < t_loop){
		pthread_mutex_lock(&mut);
		while( r_flag == 1 ) pthread_cond_wait(&var, &mut);
		w_flag = 1;
		m++;
		n++;
		w_flag = 0;
		pthread_cond_signal(&var);
		pthread_mutex_unlock(&mut);
		count++;

	}

	return NULL;

}

int main(int argc , char* argv[]){

	int i;
	pthread_t twriters[2], treaders[2];
	pthread_mutex_init(&mut, NULL);
	pthread_cond_init(&var , NULL);

	m = 0;
	n = 0;


	for(i= 0 ; i<2 ; i++){

		pthread_create(&twriters[i], NULL , writer , NULL);
		pthread_create(&treaders[i], NULL , reader , NULL );


		pthread_join(twriters[i], NULL );
		pthread_join(treaders[i], NULL );

		printf(" valor final de m é : %ld \n", m);
		printf(" valor final de n é : %ld \n", n);
	}

pthread_mutex_destroy(&mut);
pthread_cond_destroy(&var);


return 0;






}