#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <stdlib.h>

#define MAX_BUF 1024

void serverListener(void *ptr);

char buf[24];

sem_t mutex;

int main(int argc, char *argv[])
{
	pthread_t thread0;
	pthread_t thread1;
	pthread_t thread2;

	sem_init (&mutex, 0, 1);

	char *msg1 = "";

	pthread_create (&thread0, NULL, (void *) &serverListener, (void *) msg1);
	pthread_create (&thread1, NULL, (void *) &serverListener, (void *) msg1);
	pthread_create (&thread2, NULL, (void *) &serverListener, (void *) msg1);

	pthread_join (thread0, NULL);
	pthread_join (thread0, NULL);
	pthread_join (thread0, NULL);

	sem_destroy (&mutex);

	return 0;
}

void serverListener(void *ptr){
  while(1){
	sem_wait(&mutex);		


	int fd;
	char * myfifo = "/tmp/myfifo";
	char buf[MAX_BUF];

	fd = open(myfifo, O_RDONLY);
	read(fd, buf, MAX_BUF);

	//put mutex around the critical area
	//then update buffer

	int pid;
	char msg[20];
	int n = sscanf(buf, "%d", &pid);
	int numDigitsPid;
//	numDigitsPid =  floor(log10(abs(pid))) + 1;
	numDigitsPid = 5;
	printf("PID LENGTH %d\n", numDigitsPid);
	printf("pid %d\n", pid);

	
	
	char *as = &buf[numDigitsPid];
	printf("%s", as);	

	//make the string with correct path for client fifo pipe
	
	//parse pid int to str
	char pidString[10];
	sprintf(pidString, "%d", pid);
	char * tmpPath = "/tmp/";
	char clientPath[20];
	strcat(clientPath, tmpPath);
	strcat(clientPath,pidString);
	printf("client path is %s\n", clientPath);
	
	//create fifo pipe for client
	char clientBuf[MAX_BUF];
	
	mkfifo(clientPath, 0777);
	int clientPipe = open(clientPath, O_WRONLY);
	write(clientPipe, clientPath, sizeof(clientPath));
	close(clientPipe);
	unlink(clientPath);


	printf("%s\n", msg);
	//end the mutex
	sem_post(&mutex);
   }

}
