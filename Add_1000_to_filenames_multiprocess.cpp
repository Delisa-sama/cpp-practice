#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>

using namespace std;

int func(char *start_path){

	char current_path[256];
	strcpy(current_path, start_path);
	printf("current_path: %s\n",current_path);
	
	DIR *d;
	struct dirent *dir;
	errno = 0;
	int count = 0;
	int buffErr = errno;
	
	if (d = opendir(current_path))
	{
	
		while ((dir = readdir(d)) != NULL)
		{
			if ((dir -> d_type == DT_DIR) && (strcmp(dir -> d_name, ".") != 0) && (strcmp(dir -> d_name, "..") != 0))
			{
				char new_current_path[256];
				strcpy(new_current_path, current_path);
				strcat(new_current_path, "/");
				strcat(new_current_path, dir -> d_name);
				
				printf("new_current_path: %s\n",new_current_path);
				
				pid_t pID = fork();
				
				if (pID == 0)
				{
				//child
					count = 0;
					if (closedir(d) != 0) {
						printf("%s", strerror(errno));
						return 4;
					}
					if (d = opendir(new_current_path)){
						strcpy(current_path, new_current_path);
					}//
				
				} else if (pID >0)
				{
				//main
					count++;
				
				} else {
				//error
					perror("");
					return 3;
				
				}
			}
			else {
				if ((dir->d_type == DT_REG) &&
					(strlen(dir->d_name) == strspn(dir->d_name, "0123456789"))){
						
						int int_name;
						sscanf(dir -> d_name, "%d", &int_name);
						int_name += 1000;
						char oldName[256];
						strcpy(oldName, current_path);
						strcat(oldName ,"/");
						strcat(oldName ,dir->d_name);
						printf("oldName: %s\n",oldName);
						char nameBuf[256];
						char newName[256];
						sprintf(nameBuf, "%d", int_name);
						strcpy(newName, current_path);
						strcat(newName ,"/");
						strcat(newName, nameBuf);
						

						if (rename(oldName, newName) != 0){
							printf("%s!\n", strerror(errno));
							return 1;	
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
	
	
	int status;
	pid_t id;
	while ((count > 0) && ((id = waitpid(0,&status,0)) > 0) ) {
	
		if (id > 0){
			
			count--;
			
			if (!WIFEXITED(status)){
				perror("");
				return 2;
				
			}
		
		}
	
	}
	
	if (id < 0 ){
	
		perror("");
		return 1;
	
	} 
	
	
	return 0;

}

int main(){

	char start_path [256] = ".";
	
	return func(start_path);
	
}
