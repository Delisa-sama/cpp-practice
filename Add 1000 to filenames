// 
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

int req(char* path){
	DIR *d;
	struct dirent *dir;
	d = opendir(path);
	if (d) {
		errno = 0;
		int buffErr = errno;
		while ((dir = readdir(d)) != NULL) {
			if ((dir -> d_type == DT_DIR) && (strcmp(dir -> d_name, ".") != 0) && (strcmp(dir -> d_name, "..") != 0)){
				char dName[256];
				strcpy(dName, path);
				strcat(dName, "/");
				strcat(dName, dir -> d_name);
				//printf("%s", dName);
				req(dName);
			}
			else {
				if ((dir->d_type == DT_REG) &&
					(strlen(dir->d_name) == strspn(dir->d_name, "0123456789"))){
						
						//printf("%s", path);
						int int_name;
						sscanf(dir -> d_name, "%d", &int_name);
						int_name += 1000;
						char oldName[256];
						strcpy(oldName, path);
						strcat(oldName ,"/");
						strcat(oldName ,dir->d_name);
						char nameBuf[256];
						char newName[256];
						sprintf(nameBuf, "%d", int_name);
						strcpy(newName, path);
						strcat(newName ,"/");
						strcat(newName, nameBuf);
						

						if (rename(oldName, newName) != 0){
							printf("%s", strerror(errno));
							//return 2;	
						}
				}
			}
		}
		if (buffErr != errno){
			printf("%s", strerror(errno));
			errno = 0;
		}	
	}
	if (closedir(d) != 0) {
		printf("%s", strerror(errno));
		return 1;
	}
	return 0;

}


int main(){
	return req(".");
}
