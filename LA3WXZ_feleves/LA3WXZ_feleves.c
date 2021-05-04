#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
// Input tomb merete
#define max 1000
// szalak szama
#define Th_max 10

int numbers[max];
// Tomb a szalankenti maximumanak tarolasara
int max_num[Th_max] = { 0 };
int thread_no = 0;

// Maximumkivalasztas
void *maximum(void* arg)
{
	int i, num = thread_no++;
	int maxs = 0;

	for (i = num * (max / 10); i < (num + 1) * (max / 10); i++) {
		if (numbers[i] > maxs)
			maxs = numbers[i];
	}
    printf("PID: %d Szal %d. A maximum %d-%d kozott : %d \n",getpid(), thread_no, num * (max / 10), (num + 1) * (max / 10), maxs);
	max_num[num] = maxs;
}

int main()
{
	int maxs = 0;
	int i;
	char buf[32];
	int fd, ret;
	int pipefd[2];	
     pid_t cpid;
	pthread_t threads[Th_max];

	// tömb feltöltése random számokkal
    srand(time(0));
    for( i = 0; i < 1000; i++ ) {
        numbers[i] = rand();
   }
    cpid = fork();
    if (cpid == -1) {
	   perror("fork");
	   exit(-1);
    }
    if (cpid == 0) {
		printf("PID: %d : Gyerek processz \n",getpid());
		// Szalak letrehozasa
		for (i = 0; i < Th_max; i++)
			pthread_create(&threads[i], NULL,
						maximum, (void*)NULL);

		// szalak összekapcsolasa es varakozas
		// hogy mind keszen legyen
		for (i = 0; i < Th_max; i++)
			pthread_join(threads[i], NULL);

		// Finding max element in an array
		// by individual threads
		for (i = 0; i < Th_max; i++) {
			if (max_num[i] > maxs)
				maxs = max_num[i];
		}	
		fd=open("LA3WXZ",O_RDWR);
		
		sprintf(buf, "%d", maxs);
		printf("PID: %d :Ezt irom a fifoba: %s:%ld\n",getpid(),buf,strlen(buf));
		write(fd,buf,strlen(buf)); 

		exit(0);
		
		
	 } else {
		   printf("PID: %d : Szulo process\n",getpid());

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
			// FIFO kiolvasas 
			printf("PID: %d Kiolvas %d byteot. A legnagyobb elem a tombben %.*s\n",getpid(),ret, ret, buf);
			
			close(fd);
			
			unlink("LA3WXZ");	
	}

	return 0;
	
}