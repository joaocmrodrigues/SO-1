
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

/* File display program. Minimal error checking */
#define BUF_SIZE 256

int main(int argc, char *argv[]) {
   int in_fd, rd_cnt, wr_cnt, new_file;
   char buf[BUF_SIZE];
   if (argc != 3)                                 /* incorrect number of args */
      exit(1);
   in_fd = open(argv[1], O_RDONLY);               /* open source file */
   assert(in_fd > 0 );                            /* error in open */
   new_file = open(argv[2], O_RDWR|O_CREAT|O_EXCL, S_IRWXU );

   while (1) {                                 /* loop until done, or an error */
      rd_cnt = read(in_fd, buf, BUF_SIZE);        /* read from source */
      if(rd_cnt <= 0)
         break;                                   /* end of file, or error */
      wr_cnt = write(new_file, buf, rd_cnt); /* write block read */
      assert (wr_cnt >= 0);                          /* error writing */
   }
   close( in_fd);
   close(new_file);                              /* close files */
   if( rd_cnt == 0 )                              /* no error on last read */
      exit(0);
   else                                           /* error on last read */
      exit(5);
}
