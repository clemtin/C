#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */

#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */
#include <sys/types.h>  /* types implémentés différemment selon la version d’Unix */
#include <sys/stat.h>   /* constantes symboliques pour les droits d’accès */
#include <fcntl.h>      /* constantes symboliques pour les différents types d’ouverture */


#define TAILLE_BLOC 512 /* nombre d'acces d'octets par bloc*/


int main(int argc, char* argv[]){

    int src,dest;    /* DESCRIPEUR DE FICH */


    char Bloc[TAILLE_BLOC];     

    if(argc!=3){
        fprintf(stderr, "Usage: %s fich_source fich dest\n", argv[0]);
    exit(1);
    }
    
    src = open (argv[1],O_RDONLY) ; /* Ouverture du fich */
    if(src==-1){
        perror(argv[1]);
        exit(2);
    }

    dest = open(argv[2],O_WRONLY | O_CREAT |O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP);
    if(dest==-1){
        perror(argv[2]);
        close(src);
        exit(3);
    }
    
    int Nblus=0;
    int Nbecrit=0; 

    while((Nbecrit==Nblus)&&(Nblus=read(src,Bloc,sizeof(Bloc)))>0){
       Nbecrit=write(dest,Bloc,Nblus);
    }


}
