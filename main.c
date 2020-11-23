#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
	DIR *d;
	struct dirent *entry;
	struct stat sb;

	d = opendir(".");
	entry = readdir(d);

	printf("Statistics for directory: .\n");

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
