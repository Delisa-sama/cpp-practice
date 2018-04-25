

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

using namespace std;

int func(char *start_path)
{
    char current_path[256];
    strcpy(current_path, start_path);
    printf("current_path: %s\n", current_path);

    DIR *d;
    struct dirent *dir;
    struct stat file_stat;

    errno = 0;
    int count = 0;
    int *rescount = new int(0);
    int buffErr = errno;

    int fd[2];
    if(pipe(fd) == -1) {
        perror("pipe create");
        return NULL;
    };

    if(write(fd[1], &count, sizeof(count)) == -1) {
        perror("pipe write");
        return NULL;
    }

    if(d = opendir(current_path)) {
        while((dir = readdir(d)) != NULL) {
            if((dir->d_type == DT_DIR) && (strcmp(dir->d_name, ".") != 0) &&
               (strcmp(dir->d_name, "..") != 0)) {
                char new_current_path[256];
                strcpy(new_current_path, current_path);
                strcat(new_current_path, "/");
                strcat(new_current_path, dir->d_name);

                printf("new_dir: %s\n", new_current_path);

                pid_t pID = fork();

                if(pID == 0) {
                    // child
                    count = 0;
                    if(closedir(d) != 0) {
                        printf("%s", strerror(errno));
                        return 4;
                    }
                    if(d = opendir(new_current_path)) {
                        strcpy(current_path, new_current_path);
                    }

                } else if(pID > 0) {
                    // main
//                    if(close(fd[0]) == -1) {
//                        perror("close pipe");
//                        return NULL;
//                    };
                    count++;
                } else {
                    // error
                    perror("");
                    return NULL;
                }
            } else {
                if(dir->d_type == DT_REG) {
                    if(lstat(current_path, &file_stat) == -1) {
                        perror("lstat error");
                        return NULL;
                    }
                    struct tm *time_info;
                    struct tm *now_time_info;
                    time_t rowtime;

                    time(&rowtime);
                    now_time_info = localtime(&rowtime);

                    time_info = localtime(&(file_stat.st_mtime));
                    if(now_time_info->tm_year - time_info->tm_year > 1) {
                        int buff = 0;

                        if(read(fd[0], &buff, sizeof(buff)) == -1) {
                            perror("read pipe");
                            return NULL;
                        };
                        (*rescount) += 1;
                        if(write(fd[1], rescount, sizeof(*rescount)) == -1) {
                            perror("write pipe");
                            return NULL;
                        };

                        printf("%s   TRUE    count: %d\n", dir->d_name,
                               *rescount);
                    } else {
                        printf("%s   FALSE   count: %d\n", dir->d_name,
                               *rescount);
                    }
                }
            }
        }
    }

    if(buffErr != errno) {
        printf("%s", strerror(errno));
        errno = 0;
    }

    if(closedir(d) != 0) {
        printf("%s", strerror(errno));
        return -1;
    }
//    printf("count of forks: %d", count);
    int status;
    pid_t id;
    while((count > 0) && ((id = waitpid(0, &status, 0)) > 0)) {
        if(id > 0) {
            count--;

//            printf("count of forks: %d", count);
            if(!WIFEXITED(status)) {
                perror("");
                return -2;
            }
        }
    }

    if(id < 0) {
        perror("");
        return -3;
    }

    return fd[0];
}

int main()
{
    char start_path[256] = ".";

    int fd = func(start_path);
    int buff = 0;
    if(read(fd, &buff, sizeof(buff)) == -1) {
        perror("read result pipe");
    };
    if(close(fd) == -1) {
        perror("close result pipe");
        return -1;
    };
    printf("result: %d\n", buff);
    return 0;
}
