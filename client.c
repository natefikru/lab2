#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

	char input[20];
	printf("enter your input: ");
	scanf("%s", input);
	printf("this is your input: %s\n", input);
	int fd;

	char * myfifo = "/tmp/myfifo";
	mkfifo(myfifo, 0666);
	fd = open(myfifo, O_WRONLY);

	write(fd, input, sizeof(input));
	close(fd);
	unlink(myfifo);

	return 0;
}