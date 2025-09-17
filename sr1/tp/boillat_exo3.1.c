#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */
#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */
#include <errno.h>  


#define NBMOTSMAX 20
/* Construction d’un tableau de pointeurs vers le d´ebut des mots d’une cha^ıne
* de caract`eres en vue de l’utilisation de la fonction execvp.
* Retourne le nombre de mots trouv´es.
*/


int Decoupe(char Chaine[], char *pMots[]){
    char *p;
    int NbMots=0;
    p=Chaine; 
                /* On commence par le d´ebut */
                /* Tant que la fin de la cha^ıne n’est pas atteinte et qu’on ne d´eborde pas */
    while ((*p)!='\0' && NbMots<NBMOTSMAX){
        while ((*p)==' ' && (*p)!='\0') p++;       /* Recherche du d´ebut du mot */
            if ((*p)=='\0'){
                break;}                                 /* Fin de chaine atteinte */
    pMots[NbMots++]=p;                      /* Rangement de l’adresse du 1er caract`ere du mot */
        while ((*p)!=" " && (*p)!='\0') p++;            /* Recherche de la fin du mot */
            if ((*p)=="\0")break;                              /* Fin de cha^ıne atteinte */
            *p='\0';                                    /* Marquage de la fin du mot */
            p++;                                    /* Passage au caract`ere suivant */
    }
    pMots[NbMots]=NULL;                         /* Derni`ere adresse */
    return NbMots;
    }




int main(int argc, char *argv[]){
    
    
        

    /*
    pid_t lespid[argc];
    for(int i=1;i++;i<argc){
        lespid[i]=fork();
        if(lespid[i]==-1){
            printf("fork num %d\n",i);
            perror("fork");
        }
        if(lespid){ /*PERE
            exit(1);
        }
        else{
            execvp(pMots[i],pMots);
            exit(1);
        }



    }
*/    

    
    

    for(int i=1;i<argc;i++){
        pid_t pid=fork();
        if(pid==-1){
            perror("fork");
        }
        if(pid){    /* PERE */
            printf("[%d] j'ai delegué %s à %d j'attends la fin \n",getpid(),argv[i],pid);
            exit(1);
        }
    
        else{/* FILS */
            char *pMots[NBMOTSMAX+1];
            Decoupe(argv[i],pMots);
            execvp(pMots[i],pMots[i]);
            exit(1);

        }
   }
}