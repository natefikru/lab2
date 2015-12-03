#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

	DIR *dir;
	struct dirent *ent;
	char cwd[1024];

int main(void){

//TODO add command input prompt and determine what user input is


//saves current working directory as variable cwd
	if (getcwd(cwd, sizeof(cwd)) != NULL){
       fprintf(stdout, "Current working dir: %s\n", cwd);
	}
    else{
       perror("getcwd() error");
    return 0;
	}
	
//opens working directory and prints out files and directories within directory
//TODO implement the ls -l command showing long format of directory contents
	if ((dir = opendir (cwd)) != NULL) {
	  while ((ent = readdir (dir)) != NULL) {
	    printf ("%s\n", ent->d_name);
	  }
	  closedir (dir);
	} 
	else {
	  /* could not open directory */
	  perror ("directory could not be opened\n");
	  return EXIT_FAILURE;
	}


//TODO grep command
 
 
//TODO find command
}