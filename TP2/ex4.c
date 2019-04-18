#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 512




int main(int argc , char * argv[]){

	int fd, wr , rd , pos , new_file, i=0, offset;

	char buf[BUF_SIZE], samplebuf[BUF_SIZE];

	fd = open(argv[1], O_RDONLY, S_IRWXU);

	if(fd < 0 ) printf("erro a abrir o ficheiro\n");

	while ((rd = read(fd, buf, BUF_SIZE )) > 0 ){
		wr = write ( STDOUT_FILENO, buf , rd);
		i++;

	}
	printf(" executed while  %d  vezes\n", i);

	pos = lseek(fd , 0 , SEEK_SET);

	if(pos < 0) printf("erro a definir offset\n");

	//printf(" %d\n", pos);

	offset = atoi(argv[2]);

	pos = lseek(fd, offset, SEEK_SET);

	if(pos < 0) printf("erro a definir offset\n");
 
	rd = read(fd, samplebuf , BUF_SIZE  );

	//printf("sampled file: \n");

	new_file = open("sampled.smp", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

	wr = write( new_file, samplebuf , rd);
	printf("\n");

	close(fd);
	close(new_file);
	return 0;









}

