#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int Nieme(int n, int fd) {
    int entier;
    if(lseek(fd, (n-1)*sizeof(int), SEEK_SET) == -1){
        perror("Erreur 1");
        exit(3);
    }
    if(read(fd,(void*)&entier,sizeof(int))==-1){
        perror("Erreur 2");
        exit(4);
    }
    return entier;                     // le renvoie
}

void ecrire_nieme(int n,int entier,int fd){
        if(lseek(fd, (n-1)*sizeof(int), SEEK_SET) == -1){
        perror("Erreur 3");
        exit(3);
    }
    if(write(fd,(void*)&entier,sizeof(int))==-1){
        perror("Erreur 4");
        exit(4);
    }
}


int main(int argc,char *argv[]){
    if(argc!=4 || argc!=3){
        fprintf(stderr,"Usage : %s position [N] fichier \n",argv[0]);
        exit(1);
}

    if(argc==3){
        int n = atoi(argv[1]);
        int f=open(argv[2],O_RDONLY);
        if(f==-1){
            perror(argv[2]);
        }
        Nieme(n,f);
    }

    if(argc==4){
        int n = atoi(argv[1]);
        int pos = atoi(argv[2]);
        int f=open(argv[3],O_RDONLY);
        if(f==-1){
            perror(argv[2]);
    }
        ecrire_nieme(n,pos,f);
}
    return 0;
}
