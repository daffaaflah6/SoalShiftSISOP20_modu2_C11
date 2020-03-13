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

int cek_bintang(char array[]){
    if(array[0] == '*'){
        return 1;
    }
    return 0;
}
int check_number(char array[]){
    for(int i=0; i<strlen(array); i++){
        if(array[0]<'0' || array[0]>'9'){
            return 0;
        }
        return 1;
    }
}
  
int main(int argc, char** argv){
    if(argc==5){
        int waktu[4], i;
        for(i=1; i<4; i++){
            if(check_number(argv[i])){
                sscanf(argv[i], "%d", &waktu[i]);;
            } else if(cek_bintang(argv[i])){
                waktu[i] = -1;
            } else {
                printf("argument %d  is not valid.\n", i);
                exit(EXIT_FAILURE);
            }
        }

        if(waktu[0] > 59 && waktu[1] > 59 && waktu[2] > 23){
            printf("argument is not valid.\n");
        }

        for(i=1; i<5; i++){
                printf("%d\n", waktu[i]);
                printf("%s\n", argv[i]);
        }

        pid_t pid, sid;

        pid = fork();

        if (pid < 0){
        exit(EXIT_FAILURE);
        }

        if (pid > 0){
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
            int skrg1, skrg2, skrg3;

            skrg1 = local->tm_hour;
            skrg2 = local->tm_min;
            skrg3 = local->tm_sec;

            if((skrg1 == waktu[3] || waktu[3] == -1) && (skrg2 == waktu[2] || waktu[2] == -1) && (skrg3 == waktu[1] || waktu[1] == -1)){
                char *arg[] = {"bash", argv[4], NULL};
                execv("/bin/bash", arg);
        } sleep(1);
        }
    } else {
            printf("argument is not valid.\n");
    }
}