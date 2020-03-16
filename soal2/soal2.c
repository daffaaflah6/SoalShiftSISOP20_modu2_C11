#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <wait.h>

int main(){
    pid_t pid, sid;

    pid = fork();

    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while(1){
        time_t now;
        time(&now);
        struct tm *local = localtime(&now);
        char dirname[100];
        pid_t c;
        c = fork();

        strftime(dirname, 100, "%G-%m-%d_%H:%M:%S", local);
        if(c==0){
            c = fork();
            if(c==0){
                execl("/usr/bin/mkdir", "mkdir", "-p", dirname, NULL);
                }
                wait(NULL);

            for(int i=0; i<20; i++){
                c = fork();
                if(c==0){
                    time_t now1;
                    time(&now1);
                    struct tm *local1 = localtime(&now1);
                    char web[100];
                    char name[100];
                    int pixel;

                    pixel=now1%1000+100;
                    snprintf(web, 100, "https://picsum.photos/%d", pixel);
                    strftime(name, 100, "%G-%m-%d_%H:%M:%S.jpg", local1);
                    chdir(dirname);
                    execl("/usr/bin/wget", "wget", web, "-O", name, NULL);
            }
            sleep(5);
            wait(NULL);
        }
        }
        sleep(30);
    }
} 