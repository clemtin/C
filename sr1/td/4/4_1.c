#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define TAILLE 512


int main(int argc, char *argv[]){
    if(argc!=2){
        fprintf(stderr,"utilisation % nom fichier\n",argv[0]);
        exit(1);
    }

    struct stat Infos;
    if(lstat(argv[1],&Infos)!=0){ /* lstat pour avoir les liens symboliques */
        perror(argv[1]);
        exit(2);
    }

    printf("%s: \n",argv[1]);
    printf("Taille %ld octets\n",Infos.st_size);
    printf("Derniere modification :%s\n",ctime(&Infos.st_mtime));    
    exit(0);
}