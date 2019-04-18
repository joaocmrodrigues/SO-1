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

#define tamanho_stack_Max 10 

int actual_size=0;

struct stack_el{

char *str;	/* String to be printed in show() */
int n;		/* integer to be printed in show() */
struct  stack_el *next  ; /* link to next stack element*/


}stack_el;


struct stack_el *new(int n , char *str){

	struct stack_el *new = malloc(sizeof(stack_el));
	new->str = malloc(sizeof(strlen(str)));
	new->n = n;
	actual_size++;
	return new;	
}


int stack_size(struct stack_el *el ){
	if(el == NULL ) return 0;

	int n=1;

	struct stack_el *aux = el;
	while(aux->next != NULL  ){
		aux = aux->next;
		n++;
	}
return n;
}


int push (struct stack_el *el , int my_n , char *my_str){
	
	if(el == NULL || actual_size == tamanho_stack_Max  ) return 0;




	struct stack_el *new = malloc(sizeof(stack_el));

	new->str = malloc(sizeof(strlen(my_str)));
	strcpy(new->str,my_str);
	new->n = my_n;
	new->next = NULL;
	struct stack_el *aux = el;
	while( aux->next != NULL) aux= aux->next;

	aux->next = new;

	actual_size++;


	return 0;
}


int pop ( struct stack_el *el){

	if(el == NULL || actual_size == 0 ) return 0;

	struct stack_el *aux = el;

	while(aux->next->next != NULL ){
		aux= aux->next;
	}
	
	//free(aux->next);
	aux->next = NULL;


	return 0;


}


int show( struct stack_el *el)
{
	if( el == NULL  || actual_size == 0) return 0;

	struct stack_el *aux = el;
	int tamanho = stack_size(aux);
	int n_vec[tamanho];
	char *str_vec[tamanho];

	while(aux->next != NULL){
		int i=0;
		strcpy(str_vec[i], aux->str);
		n_vec[i] = aux->n;
		aux = aux->next;
		i++;
}

for(int j = actual_size ; j >= 0 ; j--){
	printf("%dº elemento da stack: %s %d \n",j, str_vec[j], n_vec[j]);

}

return 0;
}

