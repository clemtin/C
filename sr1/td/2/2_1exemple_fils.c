#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */
#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */
#include <errno.h>                  /* pour errno */

int main(int argc, char* argv[]){
    pid_t pid;

    pid=fork();
    if(pid==-1){
        perror("creation de processus");
        exit(1);}

    if(pid){
        execlp("ls","ls","-l",NULL); /* "NOM DU FICH","NOM CMD","NOM ARG","NULL" */
        }

    wait(NULL);
    execlp("DATE","date",NULL);
        /* bout de code executé par le FILS*/
    }
