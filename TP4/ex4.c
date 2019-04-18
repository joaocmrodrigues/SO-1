/*
o programa deve ser inicializado com dois argumentos:
1º - tamanho do vetor 
2º - nº de threads
*///////////////////////////////////////////////////////////////////////////////
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
#include <string.h>



typedef struct  __my_elements{

		int n_elementos;
		
		//int vec[40];
		int *vec ;

	}my_elements ;


	void *subvec(void * arg){

		my_elements *op = (my_elements*)arg;
		int i;
		op->vec = malloc(sizeof(int)*op->n_elementos);
		for(i = 0 ; i< op->n_elementos ; i++){
			op->vec[i] = i;

		}
		//strcpy(output, op->vec);
		return NULL; //(void *)output;
	}

int main( int argc , char* argv[]){


	int  n_threads, i,  tamanho_vetor, count = 0;
	tamanho_vetor = atoi(argv[1]);
	n_threads = atoi(argv[2]);

	//int *v[n_elementos];
	pthread_t t[n_threads];

	int rc[n_threads];

	my_elements args[n_threads];

	for(i = 0 ; i< n_threads ; i++){
    
		if( tamanho_vetor == n_threads) args[i].n_elementos = 1;
		else{
				float t_divisions = (tamanho_vetor%n_threads);
					if(t_divisions == 0) args[i].n_elementos = (tamanho_vetor/n_threads);


			}
			
			rc[i] = pthread_create(&t[i] , NULL , subvec , &args[i] );
			assert(rc[i] == 0);

			//pthread_join(t[i], (void **)&v );
			pthread_join(t[i], NULL);

		}

		for(int j = 0 ; j < n_threads ; j++){

			for(int i = 0 ; i < args[j].n_elementos ; i++){
			
				count ++;
				printf("o elemento nº %d do vetor = %d\n",count, args[j].vec[i] );
			}
	}





	}


		









