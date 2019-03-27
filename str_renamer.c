#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>


int renamer(char *pathname, char *old, char *new){
	int instances = 0;
	DIR *mdir;
	struct dirent *direntbuf;
	struct stat statbuf;

	if((mdir = opendir(pathname)) == NULL){
		perror(pathname);
		exit(1);
	}

    chdir(pathname);

	while((direntbuf = readdir(mdir)) != NULL){
		stat(direntbuf->d_name, &statbuf);

		if(S_ISDIR(statbuf.st_mode)) {
			if((strcmp(direntbuf->d_name, ".") != 0) && (strcmp(direntbuf->d_name, "..") != 0)){
				instances += renamer(direntbuf->d_name, old, new);
				chdir("..");
			}
		} else {
			// Remove all files which names not contain the selected substring
			if(!strcmp(direntbuf->d_name, old) != 0){
				rename(direntbuf->d_name, new);
				instances++;
			}
		}
	}
	return instances;
}

int main(int argc, char **argv){
	struct stat statbuf;

	if(argc != 4){
		printf("Usage: %s <dir> old_filename new_filename\n", argv[0]);
		exit(1);
	}

	stat(argv[1], &statbuf);
	if (S_ISDIR(statbuf.st_mode)) {
		printf("%d instances renamed\n", renamer(argv[1], argv[2], argv[3]));
	}

	return 0;
}