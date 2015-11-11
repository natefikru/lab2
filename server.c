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

	sem_init(&mutex, 0, 1);

	char *msg1 = "";

	pthread_create (&thread0, NULL, (void *) &serverListener, (void *) msg1);
	pthread_create (&thread1, NULL, (void *) &serverListener, (void *) msg1);
	pthread_create (&thread2, NULL, (void *) &serverListener, (void *) msg1);

	pthread_join (thread0, NULL);
	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);

	sem_destroy(&mutex);

	return 0;
}

void serverListener(void *ptr){
  while(1){
	sem_wait(&mutex);		

	int fd;
	char * myfifo = "/tmp/myfifo";
	char buf[MAX_BUF];

	fd = open(myfifo, O_RDONLY);
	printf("FD STATUS %d\n", fd);
	
	read(fd, buf, MAX_BUF);
	printf("buf conents %s\n", buf);
	
	

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

//	sem_post(&mutex);	
	
	char *firstName = &buf[numDigitsPid];
	
		
	char * lastName;
	printf("FIRST NAME IS %s\n", firstName);
	if(strcmp(firstName,"Tom") == 0){
	   lastName = "Cruise";
	}
	else if(strcmp(firstName, "Bob") == 0){
	    lastName = "Dylan";
	}
	else if(strcmp(firstName, "Mark") == 0){
	   lastName = "Langanki";
	}
 	else if(strcmp(firstName, "Matt") == 0){
  	   lastName = "Damon";
        }
	else if(strcmp(firstName, "Ben") == 0){
	   lastName = "Affleck";
	}
	else if(strcmp(firstName, "Selena") == 0){
          lastName = "Gomez";
	}
	else if(strcmp(firstName, "Kate") == 0){
	  lastName = "Winslet";
	}
	else if(strcmp(firstName, "Hillary") == 0){
          lastName = "Clinton";
	}

	printf("Requested Last Name is: %s\n", lastName);

	//make the string with correct path for client fifo pipe


	//parse pid int to str, concatanate proper string for path to client fifo
	char pidString[10];
	sprintf(pidString, "%d", pid);
	char * tmpPath = "/tmp/";
	char clientPath[50];
	strcat(clientPath, tmpPath);
	strcat(clientPath,pidString);
	
	//create fifo pipe for client
	char clientBuf[MAX_BUF];
	mkfifo(clientPath, 0666);
	int clientPipe = open(clientPath, O_WRONLY);
	write(clientPipe, lastName, sizeof(lastName));
	close(clientPipe);
	unlink(clientPath);
	
	//end the mutex
	sem_post(&mutex);
	
	pthread_exit(0);

  }

}
