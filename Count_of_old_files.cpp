#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int req(char* path)
{
    DIR* d;
    struct stat file_stat;
    
    struct dirent* dir;
    int count = 0;
    d = opendir(path);
    if(d) {
        errno = 0;
        int buffErr = errno;
        while((dir = readdir(d)) != NULL) {
            if((dir->d_type == DT_DIR) && (strcmp(dir->d_name, ".") != 0) &&
               (strcmp(dir->d_name, "..") != 0)) {
                char dName[256];
                strcpy(dName, path);
                strcat(dName, "/");
                strcat(dName, dir->d_name);
                req(dName);
            } else {
                if(lstat(path, &file_stat) == -1) {
                    perror("lstat");
                    return 0;
                }
                struct tm* time_info;
                struct tm* now_time_info;
                time_t rowtime;

                time(&rowtime);
                now_time_info = localtime(&rowtime);

                time_info = localtime(&(file_stat.st_mtime));
                if(now_time_info->tm_year - time_info->tm_year > 1) {
                    count++;
                    printf("%s   TRUE\n",dir->d_name);
                } else {
                    printf("%s   FALSE\n",dir->d_name);
                }
            }
        }
        if(buffErr != errno) {
            printf("%s", strerror(errno));
            errno = 0;
        }
    }
    if(closedir(d) != 0) {
        printf("%s", strerror(errno));
        return 1;
    }
    return count;
}

int main() { 
    printf("Count of files: %d\n", req("."));
    return 0;
}
