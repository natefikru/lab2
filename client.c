#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUF 1024


int main()
{


	pid_t pid;
	pid = getpid();


	char pid_string[10];
	char input[20];
	char send_str[30];
	char tmpbuf[12];

	
	sprintf(tmpbuf, "%d", pid);
	strcat(pid_string,tmpbuf);




	printf("enter your input: ");
	scanf("%s", input);
	char sendString[50];
	sendString[30] = input;
	strcat(send_str, pid_string);
	printf("PID STRING: %s\n", pid_string);
	strcat(send_str, input);
	printf("this is your input: %s\n", send_str);
	int fd;


	printf("SIZE DATA %d\n", sizeof(send_str));
	
	char * myfifo = "/tmp/myfifo";
	mkfifo(myfifo, 0666);
	fd = open(myfifo, O_WRONLY);

	
	write(fd, send_str, sizeof(send_str));
	close(fd);
	unlink(myfifo);

	//open fifo pipe from server
	char tmpPath[10] = "/tmp/";
	char returnFifo[40];
	strcat(returnFifo, tmpPath);
	strcat(returnFifo, pid_string);
	printf("return path is %s|\n", returnFifo);
	

	//open return fifo pipe
	int returnPipe;
	char returnBuf[MAX_BUF];
	returnPipe = open(returnFifo, O_RDONLY);
	read(returnPipe, returnBuf, MAX_BUF);
	char * msg = returnBuf;
	printf("return size of buffer %d\n", sizeof(returnBuf));	
	printf("char 1 %c", returnBuf[1]);


	
	
	return 0;
}
