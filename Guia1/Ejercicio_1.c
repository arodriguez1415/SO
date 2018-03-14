#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define INITIALSPACES 5
 
int main(int argc, char **argv){

    if(argc != 2) {
        printf("Cantidad incorrecta\n");
        return 1;
    }  

    DIR *dirp;   
    struct stat fileStat;
    struct dirent *direntp;
    char * path = "";
    if(stat(argv[1],&fileStat) < 0) {
        return 1;
        printf("Error en archivo\n");
    } 

    dirp = opendir(argv[1]);
    printf("%s\n",argv[1]);
    printInformation(argv[1],INITIALSPACES);

    //printf("Nombre del directorio: %s\n",argv[1]);
    //printf("Numero de archivos dentro: \t%d\n",fileStat.st_nlink);

    //while ((direntp = readdir(dirp)) != NULL) {
      //  printf("%s -----> Type: %d\n",direntp->d_name, direntp->d_type);
        //if(! strcmp(direntp->d_name,"asd")){
          //  printInformation(direntp->d_name);
     //   }
    //}
 
    //printf("Finalizo el tree");
    //closedir(dirp);
    return 0;
}

void printInformation(char * dir, int num){
    DIR * directory;
    struct dirent * dirEntry;
    struct stat file;
    char path[100];
    char * bar = "/";

    if((directory = opendir(dir)) == NULL){
        printf("Could not open the directory: %s\n", dir);
    }

    while((dirEntry = readdir(directory)) != NULL){
        printSpaces(num);
        printf("%s\n",dirEntry->d_name);
        stat(dirEntry->d_name,&file);
        //if(S_ISDIR(file.st_mode) && strcmp(dirEntry->d_name,".") != 0 && strcmp(dirEntry->d_name,"..") != 0){
        if(dirEntry->d_type == 4 && strcmp(dirEntry->d_name,".") != 0 && strcmp(dirEntry->d_name,"..") != 0){
            strcpy(path,dir);
            strcat(path,bar);
            strcat(path,dirEntry->d_name);
            printInformation(path, num + INITIALSPACES);
        }
    }
    closedir(directory);
}

void printSpaces(int num){
    int i;
    for(i = 0; i < num; i++){
        printf(" ");
    }
}