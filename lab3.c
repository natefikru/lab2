#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <limits.h>

	int getUserInput();
	int lsCommand();
	int findCommand();
	int grepCommand();

	DIR *dir;
	struct dirent *ent;
	struct stat fileStat;
	char cwd[1024];
	char str[100];
	char findStr[100];
	const char *findPath;

	int shouldTraverse = 1;

	char arg1[40];
	char arg2[40];
	char arg3[40];

int main(){

//saves current working directory as variable cwd
	if (getcwd(cwd, sizeof(cwd)) != NULL){
       fprintf(stdout, "Current working dir: %s\n", cwd);
	}
    else{
       perror("getcwd() error");
    return 0;
	}

	int executionCode = getUserInput();
	//ls
	if (executionCode == 0){
	   lsCommand();
	}

	//find
	if (executionCode == 1){
	    traverseDir(cwd);
	}

	//grep

	if (executionCode == 2){
	   grepCommand();
	}

}


//get user input
int getUserInput(){

	printf("enter input\n");
	scanf( "%s %s %s", arg1,arg2,arg3);
	printf( "%s %s %s\n", arg1,arg2,arg3);

	int returnCode = -1;
	if (strcmp(arg1, "ls") == 0){

	    returnCode = 0;
        }
	if (strcmp(arg1, "find")==0){
	    returnCode = 1;
	}
	if(strcmp(arg1, "grep")==0){
	    returnCode = 2;
	}

	return returnCode;
}



//ls -l
//Run when ls command is inputted by user
int lsCommand(){
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
//		  return EXIT_FAILURE;
		}
	}

//TODO grep command
int grepCommand(){

	char textFile[100];
	char word[100];
	int count = 0;



	//combine file name with cwd
	char *paren = "/";
	strcat(cwd, paren);
	strcat(cwd, arg2);

	FILE* file = fopen(cwd, "r");
	char line[256];

	while(fgets(line, sizeof(line), file)){
		if(strstr(line, arg2) != NULL){
			printf("%d %s", count, line);
		}
		count++;
	}
}


int traverseDir(const char *dir_name){
    DIR * dir;
    dir = opendir (dir_name);

    //check for bad dir

    if(!dir){
	fprintf(stderr, "ERROR: CANNOT OPEN DIR\n");
    }


    while (shouldTraverse == 1) {
        struct dirent * entry;
        const char * d_name;

        entry = readdir (dir);

	//check to see if dir is empty, 
        if (! entry) {
            break;
        }

        d_name = entry->d_name;

	if(strcmp(d_name, findStr) == 0)
	{
		printf("find hit \n");
		findPath = dir_name;
		printf("%s/%s\n" , findPath,d_name);
	}


        if (entry->d_type & DT_DIR) {
            /* Check that the directory is not "d" or d's parent. */
            
            if (strcmp (d_name, "..") != 0 &&
                strcmp (d_name, ".") != 0) {
                int path_length;
                char path[PATH_MAX];
 
                path_length = snprintf (path, PATH_MAX,
                                        "%s/%s", dir_name, d_name);
                traverseDir(path);
            }
	}
    }
    /* After going through all the entries, close the directory. */
    if (closedir (dir)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
} 




