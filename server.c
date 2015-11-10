#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAX_BUF 1024
#include <string.h>
typedef struct{
	int pid;
	char *name;
}nameData;

int main()
{
	int fd;
	char * myfifo = "/tmp/myfifo";
	char buf[MAX_BUF];
	nameData data;
	fd = open(myfifo, O_RDONLY);
	read(fd, buf, MAX_BUF);
	int pid;
	int n = sscanf(buf, "%d", &pid);
	printf("pid %d\n", pid);:w

//		if(strcmp(buf, "hi") == 0){

//			printf("Received: %s\n", buf);
//			printf("Returned: Hello!");
//			close(fd);
//		}
//
//		else if(strcmp(buf, "nate") == 0){
//			printf("Received: %s\n", buf);
//			printf("Returned: fikru");
//			close(fd);
//		}
//
//		else if(strcmp(buf, "kevin") == 0){
//			printf("Received: %s\n", buf);
//			printf("Returned: mueller");
//			close(fd);
//		}
//		else{
//		   printf("Received: %s\n", buf);
//		   printf("Returned: Random Message");
//		}
 //   }
	return 0;
}
