#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */
#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */
#include <errno.h>  
#include <sys/types.h>
#include <sys/wait.h>

#define NBPROC 4    /* NBR DE PROCESSUS FILS*/
#define N 10

void affichage(pid_t pid){
    int k;
    for(k=0;k<N;k++){
        printf("[%d]: c'est moi !\n",(int)pid);
        sleep(2);
    }

}

void main(void){
    pid_t pid_fils;
    int i;
    pid_t successeur;

    for(i=NBPROC; i>0;i--){
            switch (pid_fils=fork()){

            case -1:    /* PROBLEME*/
                perror("Echec creation fils: ");
                exit(EXIT_FAILURE);
            case 0: /* je suis le fils*/
                printf("Je suis le fils %d; je m'apelle %d ; mon successeur est %d.\n",i,
                    (int)getpid(),(int)successeur);
                affichage(getpid());
                printf("[%d] : Adieu.\n",(int)getpid());
                exit(i);
            default: /* je suis le pere*/
            successeur=pid_fils;
            }

    }



    /* le successuer de pere est le dernier fils */

    printf("je suis le pere ; je m'apelle %d ; mon sucesseur est %d.\n"
        ,(int)getpid(),(int)successeur);

    pid_t fils_termine;
    int retour;
    while((fils_termine=wait(&retour)) !=-1){
        printf("[%d] : Mon fils %d est terminé avec le code %d \n",
            (int)getpid(),(int)fils_termine,WEXITSTATUS(retour));}

    printf("[%d] : Tous mes fils sont terminés, adieu.\n", (int)getpid());
    exit(EXIT_SUCCESS);
    
        
    

}