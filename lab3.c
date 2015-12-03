#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

	DIR *dir;
	struct dirent *ent;
	struct stat fileStat;
	char cwd[1024];
	char str[100];

int main(char **argv){

	printf("Enter your command\n");
	scanf("%s", str);

//saves current working directory as variable cwd
	if (getcwd(cwd, sizeof(cwd)) != NULL){
       fprintf(stdout, "Current working dir: %s\n", cwd);
	}
    else{
       perror("getcwd() error");
    return 0;
	}

//ls -l
//Run when ls command is inputted by user
	if(strcmp(str, "ls") == 0){
		if ((dir = opendir (cwd)) != NULL) {
			//iterates through directory while setting dirent structure
			while ((ent = readdir (dir)) != NULL) {
			    char *paren = "/";
			    getcwd(cwd, sizeof(cwd));
			    strcat(cwd, paren);
			    strcat(cwd, ent->d_name);

			    //sets up the stat structure
			    if(stat(cwd, &fileStat) < 0){
			    	return 1;
			    }

			    //sets up the format for the date string
			    char buff[20];
			    struct tm * timeinfo;
			    timeinfo = localtime (&(fileStat.st_mtime));
			    strftime(buff, 20, "%b %d %H:%M", timeinfo);

			    //prints out permission info
			    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
			    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
			    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
			    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
			    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
			    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
			    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
			    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
			    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
			    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
			    printf(" ");
			    printf("%d ", fileStat.st_uid);
			    printf("%d ", fileStat.st_gid);
			    printf("%zu ", fileStat.st_size);
			    printf("%s ", buff);
			    printf ("%s\n", ent->d_name);
		  }
		  closedir (dir);
		} 
		else {
		  /* could not open directory */
		  perror ("directory could not be opened\n");
		  return EXIT_FAILURE;
		}
	}

//TODO grep command
 
 
//TODO find command
}