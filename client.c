#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>




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
	printf("%s\n", pid_string);
	strcat(send_str, input);
	printf("this is your input: %s\n", send_str);
	int fd;


	printf("SIZE DATA %d\n", sizeof(send_str));
	
	char * myfifo = "/tmp/myfifo";
	mkfifo(myfifo, 0666);
	printf("work");
	fd = open(myfifo, O_WRONLY);

	
	write(fd, send_str, sizeof(send_str));
	printf("test");
	close(fd);
	unlink(myfifo);

	return 0;
}
