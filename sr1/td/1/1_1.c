#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */
#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */






int main(int argc, char * argv[]){
   
   
    /*
    while(a !='\0') {
        printf(a,"%s");
        i++;
    }    
*/
    // boucle for possible car argc = nbr d'argument
    for(int i=0;i<argc;i++){
        printf("argv[%d]=%s\n",i,argv[i]);}
    exit(0);    
}