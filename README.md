# SoalShiftSISOP20_modul2_C11
Marsha Nabilah Wibowo (05111840000027) || Muhammmad Daffa' Aflah Syarif (05111840000030)

# 1. Program C menyerupai Crontab
Source Code : [soal1.c](https://github.com/daffaaflah6/SoalShiftSISOP20_modul2_C11/blob/master/soal1/soal1.c)

Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:
a. Program menerima 4 argumen berupa:
i. Detik: 0-59 atau * (any value)
ii. Menit: 0-59 atau * (any value)
iii. Jam: 0-23 atau * (any value)
iv. Path file .sh
b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai
c. Program hanya menerima 1 config cron
d. Program berjalan di background (daemon)
e. Tidak boleh menggunakan fungsi system()

```c
int cek_bintang(char array[]){
    if(array[0] == '*'){
        return 1;
    }
    return 0;
}
```
- Untuk mengecek apakah ada * di argumen yang dimasukkan. Apabila ada akan me-return 1 yang berarti benar.

```c
int check_number(char array[]){
    for(int i=0; i<strlen(array); i++){
        if(array[0]<'0' || array[0]>'9'){
            return 0;
        }
        return 1;
    }
}
```
- Untuk mengecek apakah inputan yang dimasukkan benar merupakan integer. Apabila bukan integer akan me-return nilai 0.

```c
if(argc==5)
```
- Digunakan untuk mengecek apakah argumen benar ada 5 (termasuk run program) apabila tidak akan langsung masuk ke else untuk error.

```c
int waktu[4], i;
        for(i=1; i<4; i++){
            if(check_number(argv[i])){
                sscanf(argv[i], "%d", &waktu[i]);
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
```
- Digunakan untuk melihat apakah ada error apa tidak. Apabila berupa integer akan dipindah ke array waktu yang berisi integer, apabila berupa * akan ditandai di array waktu dengan -1, selain itu akan ditunjukkan kalau argument tidak valid dan exit.

```c
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
```
- Digunakan untuk membentuk daemon.

```c
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
        } 
        sleep(1);
        }
```
- Variable skrg1, skrg2, skrg3 digunakan untuk menyimpan waktu sekarang dan dicocokkan dengan yang sudah diinput agar berjalan sesuai jam yang diinput.

# 2. Program impian Kiwa
Source Code : [soal2.c](https://github.com/daffaaflah6/SoalShiftSISOP20_modul2_C11/blob/master/soal2/soal2.c)

# 3. Folder dalam Folder
Source Code : [soal3.c](https://github.com/daffaaflah6/SoalShiftSISOP20_modul2_C11/blob/master/soal3/soal3.c)

Dalam persoalan ini ada 4 soal :
a. Membuat program dimana membuat 2 direktori, direktori pertama diberi nama "indomie", direktori kedua "sedaap". Direktori kedua dibuat setelah 5 detik.
```c
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
```
- `pid_t child_mie = fork();` bagian ini membuat fork agar bisa menjalankan banyak proses dalam sekali menjalankan
- `if (child_mie < 0) exit(EXIT_FAILURE);` bagian ini menunjukkan jika gagal dalam membuat proses baru, kemudian program akan berhenti
- `char *argv[] = {"mkdir", "-p", "/home/syarif/sisop20/modul2/shift_modul2/soal3/indomie", NULL};` bagian ini untuk membuat direktori, `"-p"` maksudnya membuat parent direktori nya
- `while ((wait(&status)) > 0);` bagian ini untuk delay suatu proses
- `sleep(5);` bagian ini agar menjalankan proses selanjutnya setelah 5 detik

b. Meng-ekstrak file `jpg.zip` pada direktori
```c
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
```
- `pid_t child_unzip = fork();` bagian ini membuat fork agar bisa menjalankan banyak proses dalam sekali menjalankan
- `if (child_unzip < 0) exit(EXIT_FAILURE);` bagian ini menunjukkan jika gagal dalam membuat proses baru, kemudian program akan berhenti
- `char* argv[] = {"unzip", "/home/syarif/sisop20/modul2/shift_modul2/soal3/jpg.zip", NULL};` bagian ini untuk membuat direktori, `"-p"` maksudnya membuat parent direktori nya

c. Setelah meng-ekstrak file tersebut, hasil ekstrakan dipindahkan berdasarkan pengelompokkan. Jika hasil ekstrak berupa folder maka dimasukkan ke dalam `"/indomie/"` sedangkan hasil ekstrak selain folder maka dimasukkan ke dalam `"/sedaap/"`
```c
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
	        if(child_team < 0){
	          exit(EXIT_FAILURE);
	        }
          if(child_team == 0){
            char path_file[1000];
            sprintf(path_file, "/home/syarif/sisop20/modul2/shift_modul2/soal3/jpg/%s", dir->d_name);
            if(S_ISDIR(st.st_mode)){
              if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0);
              else{
		             pid_t child_txt = fork();
		             if(child_txt < 0){
		                exit(EXIT_FAILURE);
		             }
		             if(child_txt == 0){
                    char* argv[] = {"mv", path_file, "/home/syarif/sisop20/modul2/shift_modul2/soal3/indomie/", NULL};
                    execv("/bin/mv", argv);
		             }
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
```
- `while ((wait(&status)) > 0);` bagian ini untuk delay suatu proses
- `chdir("/home/syarif/sisop20/modul2/shift_modul2/soal3/jpg/");` bagian ini untuk mengubah direktori
- `DIR *directory;` bagian ini pointer untuk menunjuk ke direktori
- `directory = opendir(".");` bagian ini untuk membuka direktori handle
- `struct dirent *dir;` bagian ini pointer untuk menunjukkan dalam direktori
- `if(directory)` bagian ini untuk mengecek pointer yang ditunjuk benar sebuah direktori
- `while((dir = readdir(directory)) != NULL)` bagian ini loop ketika sebuah direktori masih ada file/folder didalamnya
- `pid_t child_team = fork();` bagian ini membuat fork agar bisa menjalankan banyak proses dalam sekali menjalankan
- `struct stat st;` bagian ini pointer status dalam proses mengecek sebuah direktori
- `char path_file[1000];` bagian ini untuk menyimpan hasil pencarian
- `S_ISDIR(st.st_mode)` bagian ini fungsi untuk mengecek sebuah direktori
- `sprintf(path_file, "/home/syarif/sisop20/modul2/shift_modul2/soal3/jpg/%s", dir->d_name);` bagian ini mencari file/folder yang ada dalam direktori
- `if (child_unzip < 0) exit(EXIT_FAILURE);` bagian ini menunjukkan jika gagal dalam membuat proses baru, kemudian program akan berhenti
- `char* argv[] = {"mv", path_file, "/home/syarif/sisop20/modul2/shift_modul2/soal3/indomie/", NULL};` bagian ini untuk memindahkan folder dalam direktori ke dalam direktori `indomie`. Selain itu akan dimasukkan ke dalam direktori `sedaap`

d. Untuk setiap direktori yang sudah dipindahkan ke dalam direktori `"/indomie"` harus membuat 2 file kosong dengan penamaan `"coba1.txt"` dan `"coba2.txt"`. Untuk file `"coba2.txt"` dibuat setelah 3 detik.
```c
  //soal 3d
  while((dir = readdir(directory)) != NULL){
    pid_t child_indomie = fork();
    int kasus;
    if(child_indomie == 0){
        char target_file[1000];
        FILE *target;
        sprintf(target_file, "/home/syarif/sisop20/modul2/shift_modul2/soal3/indomie/%s/coba1.txt", dir->d_name);
        target = fopen(target_file,"w");
        fclose(target);
    }
    else{
        while((wait(&kasus)) > 0);
	      sleep(3);
 	      char target_file[1000];
	      FILE *target;
	      sprintf(target_file, "/home/syarif/sisop20/modul2/shift_modul2/soal3/indomie/%s/coba2.txt", dir->d_name);
	      target = fopen(target_file,"w");
	      fclose(target);
		    exit(0);
	   }
	 }
```
- `while((dir = readdir(directory)) != NULL)` bagian ini loop ketika sebuah direktori masih ada file/folder didalamnya
- `pid_t child_indomie = fork();` bagian ini membuat fork agar bisa menjalankan banyak proses dalam sekali menjalankan
- `char target_file[1000];` bagian ini untuk menyimpan hasil pencarian
- `FILE *target;` bagian ini pointer untuk menunjuk sebuah file/folder
- `sprintf(target_file, "/home/syarif/sisop20/modul2/shift_modul2/soal3/indomie/%s/coba1.txt", dir->d_name);` bagian ini mencari file/folder yang ada dalam direktori
- `target = fopen(target_file,"w");` bagian ini untuk membuka file/folder kemudian memberikan perintah untuk membuat file `"coba1.txt"` atau `"coba2.txt"`pada direktori
- `fclose(target); exit(0);` bagian ini untuk mengakhiri proses dalam membuat file dalam direktori
