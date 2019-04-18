#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_SIZE 1024

typedef char name[30];
typedef struct {
	name st;
	int grades[3];
}test_t;

int main(int argc , char *argv[]){

int fd, wr, rd;
char buf[BUFF_SIZE];
fd = open(argv[1], O_RDONLY, S_IRWXU );

	rd = read(fd , buf , sizeof(test_t)*3 );

	wr = write(STDOUT_FILENO, (int*)buf , sizeof(buf)-1);
	printf("\n");

close(fd);
}