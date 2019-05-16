#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]){
  int fp, wr , rc , size_input , count = 0;

  size_input = strlen(argv[1]);

  char buff[size_input];

  fp = open("/dev/echo",O_RDWR);
  if(fp<0) printf("ERRO");


  wr = write(fp, argv[1], size_input );
  if(wr <0) printf("ERRO");



  while(rc != 0){

    rc = read(fp , buff, size_input );
    count ++;


  }
  if(rc <0) printf("ERRO");

  
  printf("Bytes = %d \n", count*size_input);



  int i;
  scanf("%d", &i);

  printf(" Valor lido: %d\n", i );





  close(fp);

  printf(" PROGRAM ENDS\n");
  return 0;
}
