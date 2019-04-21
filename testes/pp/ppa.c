/* ppa.c
a) Escreva um programa que processe os argumentos da linha
de comando, inicialize a estrutura de tipo "vector_t" a usar e,
finalmente, mostre o estado do vector partilhado por via da invocação
da função "print_vector()" (incluída em util.c)

Exemplo de invocação:
     ./ppa 6000 4000
*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

vector_t vector;	// estrutura de dados a partilhar pelos threads

int main(int argc, char *argv[]) {
setbuf(stdout, NULL);

long int n1 , n2 ;

n1 = atoi(argv[1]);
n2 = atoi(argv[2]);

vector.len = (n1+n2);
vector.array = malloc(sizeof(int)*vector.len);

vector.next = vector.array[1];

//vector.lock = NULL;

for(int i = 0 ; i < 2 ; i++){
	vector.cnt[i]= 0;
}



// a preencher com o seu código!

print_vector(&vector);
return 0;
}
