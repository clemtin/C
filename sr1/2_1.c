#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */
#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */
#include <errno.h>                  /* pour errno */


int main(int argc,char* argv[]){
    pid_t pid;
    pid=fork();
    if(pid==-1){
        perror("erreur creation");
        exit(1);
    }

    if(pid){
        int pdp;
        pdp=getpid();
        printf("pid pere =%d\n",pdp);
    }

    else{
        int pdf, ppidf;
        pdf=getpid();
        ppidf=getppid();
        printf("pid du pere =%d\npid fils =%d \n",ppidf,pdf);

    }
    exit(0);
}