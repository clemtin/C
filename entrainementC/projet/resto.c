#include <stdio.h>
#include <stdlib.h>

#define TITRE 50

struct carte{
    char *entree;
    char *plat;
    char *dessert;
};

struct restaurant{
    char *nom;
    char *lieu;
    int note;
    struct carte;
    // restau suivant
};



struct carte creer_carte(){
    struct carte carteR;
    carteR.entree = malloc(TITRE * (sizeof(char)));
    carteR.plat = malloc(TITRE *(sizeof(char)));
    carteR.dessert = malloc(TITRE *(sizeof(char)));
    return carteR;
}



int main(void){
    return 0;
}

