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

#define TAILLE 512


int main(int argc,char* argv[]){
    int tube[2];
    int n=4;
    

    if(pipe(tube)==-1){
        perror("tube");
        exit(1);
    }

    int pid;
    pid=fork();
    if(pid==-1){
        perror("fork");
        exit(2);
    }

    if(pid==0){
        close(tube[1]);
        int nblus;
        while(read(tube[0],(void*)&nblus,sizeof(tube[0]))>0)
            printf("[FILS] %d\n",nblus);

        if(nblus==-1){
            perror("echec read");
            exit(3);
        }
    }
    else{/* pere*/
        close(tube[0]);
        for(int i=1; i<=n; i++){
            sleep(1);
            if(write(tube[1], &i, sizeof(i))==-1){
                perror("echec write");
                exit(3);
            }
        }
    int w;
    close(tube[1]);
    wait(&w);
    printf("[PERE] : mon fils %d est terminer avec le code %d\n",pid,WEXITSTATUS(w));
    }
    return 0;
    }

