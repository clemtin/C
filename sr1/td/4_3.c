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

void AffNomFich(char NomRep[]){
    DIR *Repertoire;
    struct dirent *Element;
    struct stat Infos;
    char Designation[512];

    Repertoire=opendir(NomRep);
    if(Repertoire==NULL){
        perror(NomRep);
        return -1;
    }
                /* boucle parcours repertoire */
    while((Element=readdir(Repertoire))!=NULL){
        if((strcmp(Element->d_name,".")!=0)&&(strcmp(Element->d_name,".."))){
            snprintf(Designation,512,"%s/%s",NomRep,Element->d_name);
        }
        if(lstat(Designation,&Infos)==0){
            if(S_ISDIR(Infos.st_mode))
            AffNomFich(Designation);
            else if(S_ISREG(Infos.st_mode))
                printf("%s\n",Designation);
        }
        else /* probleme acces au information de l'inode*/
            perror(Designation);
    


    closedir(Repertoire); 
}


