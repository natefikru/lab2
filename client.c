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

	//parse pid int to string
	sprintf(tmpbuf, "%d", pid);
	strcat(pid_string,tmpbuf);

	printf("\nCELEBRITY LAST NAME MATCHER\n");
	printf("\nTom\n");
	printf("Bob\n");
	printf("Mark\n");
	printf("Matt\n");
	printf("Ben\n");
	printf("Selena\n");
	printf("Kate\n");
	printf("Hillary\n\n");

	printf("PLEASE INPUT A CELEBRITY NAME THAT IS LISTED ABOVE.\n");
	printf("YOU WILL RECEIVE THEIR LAST NAME\n\n");
	printf("NAME MUST BE INPUTTED EXACTLY AS ABOVE!!\n");


	//allow for user input
	printf("Enter your input: ");
	scanf("%s", input);
	
//	concatanate send string with pid at front and msg following
	char sendString[50];
	sendString[30] = input;
	strcat(send_str, pid_string);
	strcat(send_str, input);
	printf("First Name: %s\n", input);
	
	//create temp fifo for server to open
	int fd;
	char * myfifo = "/tmp/myfifo";
	mkfifo(myfifo, 0666);
	fd = open(myfifo, O_WRONLY);

	//write send str to fifo,close
	write(fd, send_str, sizeof(send_str));
	close(fd);
	unlink(myfifo);

	//wait for server to create response fifo
	sleep(2);
	
	//find fifo pipe from server
	char tmpPath[10] = "/tmp/";
	char returnFifo[40];
	strcat(returnFifo, tmpPath);
	strcat(returnFifo, pid_string);
	

	//open return fifo pipe
	int returnPipe;
	char returnBuf[MAX_BUF];
	returnPipe = open(returnFifo, O_RDONLY);
	read(returnPipe, returnBuf, MAX_BUF);
	char * msg = returnBuf;
	printf("buffer contents %s\n",returnBuf);	

	return 0;
}
