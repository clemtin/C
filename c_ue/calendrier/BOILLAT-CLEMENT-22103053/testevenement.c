#include "evenement.h"
#include "date.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct sDate dated;
typedef struct sEvenement* tEvenement;

int main(void){
    
    char* titre="soiree";

    dated deb = {2024,10,5,10,10};
    dated fin = {2024,10,6,20,40}; 

    
    
    

    tEvenement MaPremiereSoiree = CreerEvenement(titre, deb, fin);
    tEvenement* Pmasoiree = &MaPremiereSoiree;

    Titre(MaPremiereSoiree);
    Debut(MaPremiereSoiree);
    Fin(MaPremiereSoiree);
    AfficheEvenement(MaPremiereSoiree);
    DetruitEvenement(Pmasoiree);

}