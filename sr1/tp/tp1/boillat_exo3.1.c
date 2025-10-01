#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */
#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */
#include <errno.h>  
#include <sys/wait.h>


#define NBMOTSMAX 20
/* Construction d’un tableau de pointeurs vers le d´ebut des mots d’une cha^ıne
* de caract`eres en vue de l’utilisation de la fonction execvp.
* Retourne le nombre de mots trouv´es.
*/

int Decoupe(char Chaine[], char *pMots[]){
  char *p;
  int NbMots=0;

  p=Chaine;	/* On commence par le début */
  /* Tant que la fin de la chaîne n'est pas atteinte et qu'on ne déborde pas */
  while ((*p)!='\0' && NbMots<NBMOTSMAX)
  {
    while ((*p)==' ' && (*p)!='\0') p++; /* Recherche du début du mot */
    if ((*p)=='\0') break;	/* Fin de chaîne atteinte */
    pMots[NbMots++]=p;		/* Rangement de l'adresse du 1er caractère du mot */
    while ((*p)!=' ' && (*p)!='\0') p++; /* Recherche de la fin du mot */
    if ((*p)=='\0') break;	/* Fin de chaîne atteinte */
    *p='\0';			/* Marquage de la fin du mot */
    p++;			/* Passage au caractère suivant */
  }
  pMots[NbMots]=NULL;		/* Dernière adresse */
  return NbMots;

}

    

void main(int argc, char *argv[]){
        char *pMots[NBMOTSMAX+1];
           
    for(int i=1;i<argc;i++){
        

        pid_t pid=fork();
        if(pid==-1){
            perror("fork");
        }

        if(pid){    /* PERE */
            printf("[%d] j'ai delegué %s à %d j'attends la fin \n",getpid(),argv[i],pid);
        }
        
        else{/* FILS */
            Decoupe(argv[i],pMots);
            printf("FILS %d va exécuter : %s\n", getpid(), pMots[i]);
            execvp(pMots[0],pMots);
            perror("execvp");
            exit(1);
        }
   }
}