#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */
#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */
#include <errno.h>                  /* pour errno */


int main(int argc, char* argv[]){

    
    int pid = fork();
    if(pid==-1){
        perror("fork");
        exit(1);
    }
    
    if(pid==0){ /* fils */
        execlp("ls","ls","-al",NULL);
        perror("ls");
        exit(1);
    }
    
    else{ /* pere */
        wait(NULL); 
        execlp("date","date",NULL);
        perror("date");
        exit(1);
    }
    exit(0);
}
