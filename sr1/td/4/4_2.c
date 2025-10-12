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

long TailleRepCour(void){
    DIR *Repertoire;
    struct dirent *Element;
    long taille = 0;    
    struct stat Infos;


    Repertoire=opendir(".");/* f=open() */
    if(Repertoire==NULL){
        perror(".");
        return -1;
    }
                /* boucle parcours repertoire */
    while((Element=readdir(Repertoire))!=NULL){
        if(lstat(Element->d_name,&Infos)==-1){
            perror(Element->d_name);
        }
        else{
            if(S_ISREG(Infos.st_mode)){
                taille=taille+Infos.st_size;
            }       
        }     
    }
    closedir(Repertoire); 
    return taille;
}


int main(){
    printf("taille repo = %d\n",TailleRepCour);
    return 0;
}