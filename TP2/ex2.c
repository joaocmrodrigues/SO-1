#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 256

int main(int argc, char *argv[]){
  int fd, wr_cnt,rd_cnt,n=2,splited_file;
  char buf[BUF_SIZE];

  fd = open(argv[1],O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
  assert(fd > 0);

  while(n < (argc)){
    splited_file = open(argv[n],O_RDONLY);
    assert( splited_file > 0);
    rd_cnt = read(splited_file, buf , BUF_SIZE);
    if(rd_cnt <= 0)
       break;
    wr_cnt = write(fd, buf , rd_cnt );
    assert(wr_cnt > 0);
    close(splited_file);
    n++;
  }
  close(fd);

  if( rd_cnt == 0 )                              /* no error on last read */
     exit(0);
  else                                           /* error on last read */
     exit(5);
}
