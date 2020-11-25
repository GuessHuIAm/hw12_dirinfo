#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv){
	char buffer[100];

	if (argc == 2){
        	strncpy(buffer, argv[1], sizeof(buffer) - 1);
    	}
	else{
		printf("Enter a directory: ");
		fgets(buffer, sizeof(buffer), stdin);
	}

	// getting rid of that new-line character
	char *position;
	if ((position = strchr(buffer, '\n')) != NULL){
		*position = '\0';
	}

	DIR *d;
	struct dirent *entry;
	struct stat sb;

	d = opendir(buffer);
	if (d == NULL){
		printf("Error: %s\n", strerror(errno));
	}
	entry = readdir(d);

	printf("Statistics for directory: %s\n", buffer);

	int s = 0;
	while (entry != NULL){
		if (entry->d_type == DT_REG){
			stat(entry->d_name, &sb);
			s += sb.st_size;
		}
		entry = readdir(d);
	}

	printf("Total Directory Size: %d Bytes\n", s);

	rewinddir(d);
	entry = readdir(d);

	printf("Directories:\n");
	while (entry != NULL){
		if (entry->d_type == DT_DIR){
			printf("\t%s\n", entry->d_name);
		}
		entry = readdir(d);
	}

	rewinddir(d);
	entry = readdir(d);

	printf("Regular files:\n");
	while(entry != NULL){
		if(entry->d_type == DT_REG){
			printf("\t%s\n", entry->d_name);
		}
		entry = readdir(d);
	}
	closedir(d);

	return 0;
}
