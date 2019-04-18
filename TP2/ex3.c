
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define NTESTES 3 


typedef char name[30];
typedef struct {
	name st;
	int grades[3];
}test_t;



int main(int argc , char *argv[]){

int fd, wr, p1, p2, p3;
//char buf[30];
 test_t teste[NTESTES];
fd = open( argv[1], O_WRONLY|O_CREAT|O_APPEND, S_IRWXU);



printf("inserir o nome do teste e a pontuação correspondente a cada pergunta.\n");
for ( int i=0 ; i< 3 ; i++){
	printf("*************************\n");
	printf("NOME DO ALUNO: ");
	scanf("%s",teste[i].st);
	//fgets(teste[i].st, 30 , stdin);
	printf("\nCOTAÇÂO 1ª PERGUNTA :");
	scanf("%d",&p1);
	printf("\nCOTAÇÂO 2ª PERGUNTA :");
	scanf("%d",&p2);
	printf("\nCOTAÇÂO 3ª PERGUNTA :");
	scanf("%d",&p3);
	printf("*************************\n");
	teste[i].grades[0]= p1;
	teste[i].grades[1]= p2;
	teste[i].grades[2]= p3;

	//strcpy(teste[i].st, buf);

	wr = write(fd ,&teste[i], sizeof(test_t));
	if(wr == -1 ) printf("ERRO WRITEEEEE");

}



close(fd);

return 0 ;
}
