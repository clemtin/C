#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "evenement.h"
#include "date.h"


/* permet d'etre plus rapide */
typedef struct sEvenement* tEvenement;

struct sEvenement{
    char* titre;
    struct sDate debut;
    struct  sDate fin;
        
};

/* verif des date avant creations de l'event dynamiquement*/
tEvenement CreerEvenement(const char* titre, struct sDate debut, struct sDate fin){

 /*          rappel des sorties de COMPARE
    COMAPRE(DATE1,DATE2) => DATE1>DATE2 => 1 SINON -1 
     */

    if((EstValide(debut)==0 || EstValide(fin)==0) || Compare(debut,fin)>0){
        return NULL;
    }
        

    tEvenement evenement = (tEvenement)malloc(sizeof(struct sEvenement));
    if (evenement == NULL){
        return NULL;
    }

    /* on implemente au champs les valeurs le malloc sur le titre doit prendre en compte la taille du titre + 1 pour \0 */

    evenement->titre = (char*)malloc((strlen(titre)+1)*sizeof(char));
    evenement->debut = debut;
    evenement->fin = fin;


    strcpy(evenement->titre,titre);
    return evenement;
}


/* evident */
char* Titre(tEvenement evenement){
    return evenement->titre;
}

/* evident */
struct sDate Debut(tEvenement evenement){
    return evenement->debut;
}
/* evident */
struct sDate Fin(tEvenement evenement){
    return evenement->fin;
}

/* on doit d'abord liberer le malloc sur le titre et apres celui de l'event */
void DetruitEvenement(tEvenement* pEvenement){
    if((*pEvenement!=NULL) && (pEvenement!=NULL)){
        free((*pEvenement)->titre);
        free(*pEvenement);
        *pEvenement=NULL;
    }
        
        
}

/* on utilise YYYY pour formater les dates puis on print les dates */
void AfficheEvenement(tEvenement evenement){
    char* deb[TAILLE_CHAINE_DATE];
    char* finish[TAILLE_CHAINE_DATE];
    YYYYMMDDTHHMM(deb,evenement->debut);
    YYYYMMDDTHHMM(finish,evenement->fin);

    printf("%s du %s au %s \n",evenement->titre,deb,finish);
}