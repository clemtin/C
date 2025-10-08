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
        while(lec=(read(Remplir[0],&lec,sizeof(lec)))>0){
            switch (lec)
            {
            case 1:
                bassin=bassin+lec;
                printf("*");
                fflush(stdout);
                if(bassin>MAX_BASSIN){
                    write(Etat[1],&bassin,sizeof(bassin));
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

        int a = -1;
        int lu;


        for(int i=1; i<=N; i++){
            sleep(1);
            if(write(Remplir[1], &i, sizeof(i))==-1){
                perror("echec write");
            if((lu=read(Etat[0],(void*)&lu,sizeof(lu)))>0)
                if(write(Remplir[1],&a,sizeof(int))==-1){
                    perror("echec de con");
                    exit(5);
                }
                exit(6);
            }
            if(lu==-1){
                perror("echec erreur pere");
            }
        }
        int codefils;
        wait(&codefils);
        printf("\n");
        printf("[PERE] : mon fils %d est terminer avec le code %d\n",pid,WEXITSTATUS(codefils));
    }

    return 0;
}
