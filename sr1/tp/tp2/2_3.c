#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TAILLE 512


void ecrire_dans_stdout (char nom_fich[]){
    int f;
    f=open(nom_fich,O_RDONLY);
    if(f==-1){
        perror("nom fich");
        exit(2);
    }

    char bloc[TAILLE];
    int nbecrit;
    int nblus = read(f,(void *)bloc,TAILLE);

    while( nblus > 0 ){
        nbecrit=write(STDOUT_FILENO,(void*)bloc,nblus);
        nblus = read(f,(void *)bloc,TAILLE);
    }

    if(nblus == -1){
        perror("echec read");
        exit(4);
    }
    if(nbecrit == -1){
        perror("echec read");
        exit(5);
    }

    close(f);

}


void ecrire_sd(char source[],char dest[]){
    int s,d;
    s=open(source,O_RDONLY);

    if(s==-1){
        perror("s");
        exit(2);
    }

    d=open(dest,O_WRONLY| O_CREAT | O_TRUNC);

    if(d==-1){
        perror("d");
        exit(3);
    }

    char bloc[TAILLE];
    int nbecrit;
    int nblus = read(s,(void *)bloc,TAILLE);

    while( nblus > 0 ){
        nbecrit=write(d,(void*)bloc,nblus);
        nblus = read(s,(void *)bloc,TAILLE);
    }

    if(nblus == -1){
        perror("echec read");
        exit(4);
    }
    if(nbecrit == -1){
        perror("echec write");
        exit(5);
    }
    close(s);
    close(d);
}


void lire_stdin(){
    int a;
    char bloc [TAILLE];
    while((a=read(STDIN_FILENO,bloc,TAILLE))>0){
        write(STDOUT_FILENO, bloc, a);
    }
    

    
}

int main(int argc,char *argv[]){
    int i;
    int cas=0;
    int a;
    int pos;
    for(i=1;i<argc;i++){
        if(argv[i]=='>'){
            cas=1;
            pos = i;
            break;
        }
    }

    if(argc==1){
        lire_stdin();
    }

    if(cas==1){
        while(i=1,i<pos,i++){
            ecrire_sd(argv[i],argv[cas+1]);
        }
        
    }

    if(cas==0){ 
        for(i=1;i<argc;i++){
            pid_t pid=fork();
            if(pid==0){ /*     FILS     */
                ecrire_dans_stdout(argv[i]);
                exit(EXIT_SUCCESS);
            }
        }

       while(wait(NULL)>0);
    }
    
}
