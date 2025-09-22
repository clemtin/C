#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */

#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */
#include <sys/types.h>  /* types implémentés différemment selon la version d’Unix */
#include <sys/stat.h>   /* constantes symboliques pour les droits d’accès */
#include <fcntl.h>      /* constantes symboliques pour les différents types d’ouverture */

/*
ex 1
off_t position;
position=lseek(fd,0,SEEK_CUR);

/* ex 2
lseek(fd,position,SEEK_SET);

/* ex 3
off_t taille =lseek(fd,0,SEEK_END);

*/


int(Nieme)(int n,int fd){
    int Entier;



    return Entier;
}