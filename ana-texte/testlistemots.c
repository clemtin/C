#include "listemots.h"

int main(){
    tListeMots liste1 = creerListeMots();
    if (liste1 == NULL){
        return 1;
    }
    ajouterMot(liste1, "Salut");
    nombreDeMot(liste1);
    ecrireListeMots(liste1, stdout);
    ajouterMot(liste1, "test");
    nombreDeMot(liste1);
    ecrireListeMots(liste1, stdout);
    ajouterMot(liste1, "Clément");
    nombreDeMot(liste1);
    ecrireListeMots(liste1, stdout);

    detruireListeMots(liste1);
    nombreDeMot(liste1);
    ecrireListeMots(liste1, stdout);
}