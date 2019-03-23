#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include<sys/wait.h>

 int pid_pai, pid_filho, pid_neto;


int main(int argc , char *argv[]){
  int aux,aux1;

  aux = fork();
  if (aux == 0){ // filho
    aux1 = fork();

      if(aux1 == 0){ //neto
        pid_filho = getppid(); //pid do filho
        printf("PID filho = %d \n", pid_filho);
        pid_neto = getpid(); //pid neto
        printf("PID neto = %d \n", pid_neto);
        return 3;
      }
    else {
    wait(NULL);     //espera que o processo neto termine
    return 2;
    }
  }
  else{
    wait(NULL); //espera que o processo filho termine
    pid_pai = getpid();
    printf("PID pai = %d \n", pid_pai);


    return 1;

  }
}
