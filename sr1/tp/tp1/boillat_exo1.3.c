#include "afficher.h"
#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */
#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */
#include <errno.h>                  /* pour errno */

int main(int argc, char* argv[]){

    id_t pid=fork();
    
    if(pid == -1)
    {
        perror("erreur fork");
        exit(1);
    }
    if(pid){ /* PERE */
        int infofils;
        wait(&infofils);
    
        printf("Je suis le PERE voici mes info:\n");
        afficher();
        printf("code retour fils = 2\n");
        printf("Code de retour du PERE  : %d\n",WEXITSTATUS(infofils));
        exit(2);
    }

    else /* FILS */
    {
        printf("Je suis le FILS voici mes info:\n");
        afficher();
        printf("code retour fils = 3\n");
        exit(3);
    }
    exit(0);
}
