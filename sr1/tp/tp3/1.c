#include <stdio.h>
#include <stdlib.h>     
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h> 



void Affiche_inode(struct stat *Infos) {
    char *type;

    if (S_ISREG(Infos->st_mode))
        type = "fichier ordinaire";
    else if (S_ISDIR(Infos->st_mode))
        type = "répertoire";
    else if (S_ISLNK(Infos->st_mode))
        type = "lien symbolique";
    else if (S_ISCHR(Infos->st_mode))
        type = "périph. caractère";
    else if (S_ISBLK(Infos->st_mode))
        type = "périph. bloc";
    else if (S_ISFIFO(Infos->st_mode))
        type = "FIFO/pipe";
    else if (S_ISSOCK(Infos->st_mode))
        type = "socket";
    else
        type = "inconnu";

    // Conversion de la date
    char *date = ctime(&Infos->st_mtime);
    // ctime() ajoute déjà un retour à la ligne → on le retire
    date[strlen(date) - 1] = '\0';

    printf("%-20s %10ld octets %s\n", type, (long)Infos->st_size, date);
}


int main(int argc, char *argv[]){
    struct stat Infos;

    if(argc<2){
        fprintf(stderr,"Usage %s nom fich [...]",argv[0]);
        exit(1);
    }

    
    if(argc>2){
    
    for(int a=1;a<argc;a++) {
        if (lstat(argv[a], &Infos) == -1) {
            perror(argv[a]);
        }
        else{
            printf("%s ", argv[a]);
            Affiche_inode(&Infos);
        }
        
    }
    }
    return 0;
}