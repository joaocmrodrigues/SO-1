#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>



int main (int argc , char *argv[], char *envp[]){


  int i,j=0,fd,wr_cnt,aux;
  char *buf;
  aux = fork();
  if(aux == 0){
    fd = open( argv[2], O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU);
    assert(fd>0);
  }
  else{
    fd = open( argv[1], O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU);
    assert(fd>0);
  }




 //printf("argc = %d \n", argc);
 for(i=0 ; i< argc; i++){
   //printf("argv[%d]= %s \n", i, argv[i]);
  buf = argv[i];
  wr_cnt = write(fd, buf , strlen(buf));
  wr_cnt = write(fd, "\n",1);

}
  while(envp[j] != NULL ){
    //printf("envp[%d]= %s \n", j , envp[j]);
    buf = envp[j];
    wr_cnt = write(fd, buf , strlen(buf));
    assert(wr_cnt>0);
    wr_cnt = write(fd, "\n",1);
    assert(wr_cnt>0);
    j++;

}

close(fd);



}
