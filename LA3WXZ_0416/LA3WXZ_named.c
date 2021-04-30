#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main() {
     int pipefd[2];	
     pid_t cpid;	
     char szoveg[32];	
    int fd, ret;
	char buf[32];

	buf[0]=0;



     cpid = fork();
     if (cpid == -1) {
	   perror("fork");
	   exit(-1);
     }

     if (cpid == 0) {    
	   printf("%d: Gyerek processz \n",getpid());
       fd=open("LA3WXZ",O_RDWR);
       strcpy(buf,"Balint Gergely \0");
	   printf("%d:Ezt irom a fifoba: %s:%ld\n",getpid(),buf,strlen(buf));
	   write(fd,buf,strlen(buf)); 

   	   exit(0);

     } else {
	   printf("%d: Szulo process\n",getpid());
       
            ret=mkfifo("LA3WXZ",00666);	
	    if (ret == -1) {
	        perror("mkfifo()");
	        exit(-1);
	    }

	    fd=open("LA3WXZ",O_RDWR);
	    if (fd == -1) {
	        perror("open() error!");
	        exit(-1);
	    }


        wait(NULL);   
	    ret=read(fd,buf,32); 
	    printf("%d:read()Kiolvas %d byteot: %s\n",getpid(),ret,buf);

	    close(fd);
        
	    unlink("LA3WXZ");	


	   exit(0);
     }
}

