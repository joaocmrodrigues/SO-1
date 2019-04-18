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
#include "stack5.h"


int main(int argc , char *argv[]){

	int my_n;
	char *my_str = malloc(sizeof(char));
	int comand, tamanho=0;

	struct stack_el *aux;
	


while(1){
	printf(" to push press 1 , to pop press 2 , to show press 3:  ");
	scanf("%d", &comand);

	if(comand == 1 ){
		if(tamanho ==0 ){
			scanf("%d %s",&my_n, my_str);
			aux = new(my_n, my_str);

		}
		else{
			scanf("%d %s",&my_n, my_str);
			push(aux, my_n, my_str);

		}


	}


	else if(comand == 2){
		pop(aux);

	}

	else if ( comand == 3){
		show(aux);
	}
}
	
}