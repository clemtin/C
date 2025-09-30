#define _POSIX_C_SOURCE 200809L

#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */

#include <unistd.h>
#include <sys/types.h>  /* types implémentés différemment selon la version d’Unix */
#include <sys/stat.h>   /* constantes symboliques pour les droits d’accès */
#include <fcntl.h>      /* constantes symboliques pour les différents types d’ouverture */

#define TAILLE 256


void ecrire_dans_stdout (char nom_fich[]){
    int f;
    f=open(nom_fich,0,O_RDONLY);
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

int main(int argc,char* argv[]){

    if(argc !=2){
        fprintf(stderr,"Usage %s fsource \n",argv[0]);
        exit(1);
    }

    ecrire_dans_stdout(argv[1]);

    return 0;
}
