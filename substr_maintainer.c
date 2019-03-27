#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>


int remover(char *pathname, char *sub){
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
				instances += remover(direntbuf->d_name, sub);
				chdir("..");
			}
		} else {
			// Remove all files which names not contain the selected substring
			if(!strstr(direntbuf->d_name, sub) != NULL){
				instances++;
				remove(direntbuf->d_name);
			}
		}
	}
	return instances;
}

int main(int argc, char **argv){
	struct stat statbuf;

	if(argc != 3){
		printf("Usage: %s <dir> substring_file_to_maintain\n", argv[0]);
		exit(1);
	}

	stat(argv[1], &statbuf);
	if (S_ISDIR(statbuf.st_mode)) {
		printf("%d instances removed\n", remover(argv[1], argv[2]));
	}

	return 0;
}
