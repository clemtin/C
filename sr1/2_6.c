#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */
#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */
#include <errno.h>                  /* pour errno */


int main(int argc, char* argv[]){

    /* pid_t = int */
    int pid=fork();

    if(pid==-1){
        perror(" fork ");
        exit(1);
    }

    if(pid==0){ /* PREMIER FILS*/
        execlp("ls","ls","-l",NULL); /* "NOM DU FICH","NOM CMD","NOM ARG","NULL" */
        perror("ls");
        exit(2);
    }

    wait(NULL);
    pid=fork();
    if(pid==-1){
        perror("creation processus 2 ");
        exit(1);}
    if(pid==0){
        execlp("pwd","",NULL);
        exit(2);}       

    exit(0);
}
    

