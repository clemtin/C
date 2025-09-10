#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>

int main(int argc, char * argv[]){
    /*
    while(a !='\0') {
        printf(a,"%s");
        i++;
    }    
*/
    // boucle for possible car argc = nbr d'argument
    for(int i=0;i<argc;i++){
        printf("argv[i]=%s\n",i,argv[i]);}
    exit(0);    
}