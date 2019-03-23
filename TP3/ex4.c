#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

int main( int argc , char *argv[], char *envp[]){

	int aux = fork();

	if( aux < 0 ){
		printf("Fork failed!!!!!!");
		exit(1);
	}
	else if(aux == 0 ){ // processo filho 

		char *newargv[] = {"/usr/bin/gcc", argv[1], "-Wextra", NULL};
		char *newenviron[] = { NULL };

		execve("/usr/bin/gcc", newargv , envp);

	}
	else{ //processo pai 
		wait(NULL);
		printf("processo terminado !!!\n");
		return 1;

	}


}