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



int main(void){
    int tube[2];

    if(pipe(tube)==-1){
        perror("echec creation tube");
        exit(1);
    }
    char c;
    switch(fork()){

        case -1:{
        perror("echec creation fils\n");
        exit(2);
        }

        case 0:{
            printf("Fils\n");
            close(tube[1]); /* tube 1 ecriture tube 0 lecture */
            while(read(tube[0],(void*)&c,sizeof(c))>0) /* passage de l'adresse de c*/
                write(STDOUT_FILENO,(void*)&c,sizeof(c));
            close(tube[0]);
            exit(0);
        }
        defaut:{
            break;
        }
    }
    printf("PERE\n");
    close(tube[0]); /* le pere est ecrivain */
    while((read(STDIN_FILENO,(void*)&c,sizeof(c))>0)&&(c!='f')){
        write(tube[1],(void*)&c,sizeof(c));
    }
    close(tube[1]); /* tres important*/
    printf("pere fini\n");
    exit(0);
}