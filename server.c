#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

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

	int fd;
	char * myfifo = "/tmp/myfifo";
	char buf[MAX_BUF];

	fd = open(myfifo, O_RDONLY);
	read(fd, buf, MAX_BUF);

	//put mutex around the critical area
	sem_wait(&mutex);
	//then update buffer

	int pid;
	int n = sscanf(buf, "%d", &pid);
	printf("pid %d\n", pid);

	//end the mutex
	sem_post(&mutex);
}