#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */
#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */

int main(int argc, char * argv[]){

    if(argc !=2){
        fprintf(stderr,"Usage; %s variable, argv[0] \n");
        exit(1);
    }

    char * valeur;
    valeur = getenv(argv[1]);
    if (valeur ==NULL){
        fprintf(stderr,"Varible %s inconnue\n");
        exit(2);
    }
    printf("%s\n");

    exit(0);
}