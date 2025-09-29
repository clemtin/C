#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */

#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */
#include <sys/types.h>  /* types implémentés différemment selon la version d’Unix */
#include <sys/stat.h>   /* constantes symboliques pour les droits d’accès */
#include <fcntl.h>      /* constantes symboliques pour les différents types d’ouverture */


void main(int argc,char* argv[]){
        
    int Entree, Sortie;

    if(argc!=4){
        fprintf(stderr,"Usage: %s commande fich entrée fich sortie ",argv[0]);
        exit(1);
    }

    Entree=open(argv[2],O_RDONLY);
    if(Entree==-1){
        perror(argv[2]);
        exit(2);
    } 

    Sortie =open(argv[3],O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if(Sortie==-1){
        perror(argv[3]);
        close(Entree);
        exit(3);
    }


    if(dup2(Entree,STDIN_FILENO)==-1)    /* redirection de stdin */
    {
        perror("Redirection entre standard");
        close(Entree);
        close(Sortie);
        exit(4);
    }
    
    if(dup2(Sortie,STDIN_FILENO)==-1)    /* redirection de stdin */
    {
        perror("Redirection entre standard");
        close(Entree);
        close(Sortie);
        exit(5);
    }
    int pid =fork();
    if(pid==-1){
        perror("Duplication processus");
        close(Entree);
        close(Sortie);
        exit(99);
    }


    if(pid==0){ /* JE SUIS LE FILS */
        execlp(argv[1],argv[1],NULL);
        perror(argv[1]);
        close(Entree);
        close(Sortie);
        exit(6);
        }    
        
        
    wait(NULL);
    close(Entree);
    close(Sortie);
    exit(0);


    /*      MA PARTIE 
        pid_t pid = fork();
        if(pid==-1){
            perror(pid);
        }
        else{
            execlp(argv[1],argv[1]);
            perror(execlp);
            exit(1);
        }
    */

    }