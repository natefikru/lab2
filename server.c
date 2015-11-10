#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#define MAX_BUF 1024

int main()
{
	int fd;
	char * myfifo = "/tmp/myfifo";
	char buf[MAX_BUF];

	fd = open(myfifo, O_RDONLY);
	read(fd, buf, MAX_BUF);

//	while(buf != "exit"){

		if(strcmp(buf, "hi") == 0){

			printf("Received: %s\n", buf);
			printf("Returned: Hello!");
			close(fd);
		}

		else if(strcmp(buf, "nate") == 0){
			printf("Received: %s\n", buf);
			printf("Returned: fikru");
			close(fd);
		}

		else if(strcmp(buf, "kevin") == 0){
			printf("Received: %s\n", buf);
			printf("Returned: mueller");
			close(fd);
		}
		else{
		   printf("Received: %s\n", buf);
		   printf("Returned: Random Message");
		}
 //   }
	return 0;
}
