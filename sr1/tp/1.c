#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */
#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */
#include <errno.h>                  /* pour errno */


int affiche_infos(){

    printf("PID : %d\n",getpid());
    printf("PPID : %d\n",getppid());
    printf("PGRP : %d\n",getpgrp());
    printf("LOGIN : %s\n",getlogin());
    printf("UID : %d\n",getuid());
    printf("GID : %d\n",getgid());
} 



int main(int argc, char* argv[]){

    id_t proc_fils=fork();
    
    if(proc_fils == -1)
    {
        perror("erreur fork");
        exit(1);
    }
    else if(proc_fils)
    {
        int infofils;
        wait(&infofils);
        printf("Code de retour du fils  : %d\n",WEXITSTATUS(infofils));
        
        printf("Je suis le PERE voici mes info:\n");
        affiche_infos();
        exit(2);
    }
    else 
    {
        printf("Je suis le FILS voici mes info:\n");
        affiche_infos();
        exit(0);
    }
    exit(0);
}
