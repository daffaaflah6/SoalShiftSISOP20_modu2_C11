#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(){
  pid_t child = fork();
  int status;
  if (child < 0){
    exit(EXIT_FAILURE);
  }
  if (child == 0){
    pid_t child_mie = fork();
    //soal 3a
    if (child_mie < 0){
      exit(EXIT_FAILURE);
    }
    if (child_mie == 0){
      char *argv[] = {"mkdir", "-p", "/home/syarif/sisop20/modul2/shift_modul2/soal3/indomie", NULL};
      execv("/bin/mkdir", argv);
    }
    else{
      while ((wait(&status)) > 0);
      sleep(5);
      char *argv[] = {"mkdir", "-p", "/home/syarif/sisop20/modul2/shift_modul2/soal3/sedaap", NULL};
      execv("/bin/mkdir", argv);
    }
  } 
  else{
    while ((wait(&status)) > 0);
    pid_t child_unzip = fork();
    //soal 3b
    if (child_unzip < 0){
      exit(EXIT_FAILURE);
    }
    if (child_unzip == 0){
      char* argv[] = {"unzip", "/home/syarif/sisop20/modul2/shift_modul2/soal3/jpg.zip", NULL};
      execv("/usr/bin/unzip", argv);
    }
    else{
      //soal 3c
      while ((wait(&status)) > 0);
      chdir("/home/syarif/sisop20/modul2/shift_modul2/soal3/jpg/");
      DIR *directory;
      directory = opendir(".");
      struct dirent *dir;
      if(directory){
        while((dir = readdir(directory)) != NULL){
          pid_t child_team = fork();
	  struct stat st;
	  stat(dir->d_name, &st);
          if(child_team == 0){
            char path_file[1000];
            sprintf(path_file, "/home/syarif/sisop20/modul2/shift_modul2/soal3/jpg/%s", dir->d_name);
            if(S_ISDIR(st.st_mode)){
              if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0);
              else{
               char* argv[] = {"mv", path_file, "/home/syarif/sisop20/modul2/shift_modul2/soal3/indomie/", NULL};
               execv("/bin/mv", argv);
              }
            }
            else{
              char* argv[] = {"mv", path_file, "/home/syarif/sisop20/modul2/shift_modul2/soal3/sedaap/", NULL};
              execv("/bin/mv", argv);
            }
          }
        }
        closedir(directory);
      }
    }
  }
}
