#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#include <dirent.h>

#define N 10
#define MAX_BASSIN 5
#define TAILLE 512


int main(int argc,char *argv[]){
    int bassin = 0;
    int Etat[2];
    int Remplir[2];
    int pid;
    

    if(pipe(Remplir)==-1){
        perror("echec pipe remplir");
        exit(2);
    }
    if(pipe(Etat)==-1){
        perror("echec pipe etat");
        exit(3);
    }

    pid=fork();
    if(pid==-1){
        perror("fork");
        exit(4);

    }

    if(pid==0){
        close(Etat[0]);  /* tube 1 ecriture tube 0 lecture */
        close(Remplir[1]); /* tube 1 ecriture tube 0 lecture */
        int lec;
        int nblus;
        while((nblus=read(Remplir[0],(void*)&lec,sizeof(lec)))>0){
            
            switch (lec){
            case (1):
                bassin+=lec;
                printf("*");
                fflush(stdout);
                if(bassin==MAX_BASSIN-1){
                    if(write(Etat[1],&bassin,sizeof(int))==-1){
                        perror("echec write bassin");
                        exit(8);
                        }
                    }
                break;
            
            case -1:
                bassin=0;
                printf("\n");
                break;
            }      
        }

        close(Etat[1]);
        close(Remplir[0]);  
        exit(1);

      }

    else{
        close(Remplir[0]); /* tube 1 ecriture tube 0 lecture */
        close(Etat[1]);

        int f_flags; /* mode non bloquant pour le tube Etat dans le P`ere */
        f_flags = fcntl(Etat[0], F_GETFL); /* R´ecup´eration des flags */
        f_flags |= O_NONBLOCK; /* Positionnement du flag de non blocage */
        fcntl(Etat[0], F_SETFL, f_flags); /* Mis `a jour des flags */

        int p= 1;
        int a = -1;
        int lu;
        int nblu;

        for(int i=0; i<N; i++){
            lu=0;
            usleep(20000);
            if(write(Remplir[1], &p, sizeof(p))==-1)
                {
                    perror("echec write");
                    exit(6);
                }

            read(Etat[0],(void*)&lu,sizeof(lu));
            if(lu==MAX_BASSIN-1){
                if(write(Remplir[1],&a,sizeof(int))==-1){
                    perror("echec de con");
                    exit(5);
                }
                }
            }
        
        close(Etat[0]);
        close(Remplir[1]);
        int codefils;
        wait(&codefils);
        printf("\n");
        printf("[PERE] : mon fils %d est terminer avec le code %d\n",pid,WEXITSTATUS(codefils));
        exit(9);
        }

        
        return 0;
    }

    
