#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

struct sImage{
    int Nblig; //nbr de lig de l'image
    int Nbcol; // nbr de col de l'image
    tMatrice NivGris; //matrice des niveaux de gris de l'image
};


tImage ImAllouer(int Nblignes, int NbColonnes){
    tImage image = malloc(sizeof(struct sImage));
    if (image == NULL){
        return NULL;
    }

    image->Nblig=Nblignes;
    image->Nbcol=NbColonnes;
    image->NivGris= MatAllouer(Nblignes,NbColonnes);


    if (image->NivGris == NULL) {
        printf("Erreur d'allocation memoire pour la matrice des niveaux de gris !\n");
        free(image);
        return NULL;
    }

    return image;
}



void ImLiberer(tImage *pIm){
    if(*pIm != NULL){
        MatLiberer(&((*pIm)->NivGris));
        free(*pIm);
        *pIm=NULL;
    }   

}

int ImNblig(tImage Im){
    return(Im->Nblig);

}

int ImCol(tImage Im){
    return (Im->Nbcol);
}

tMatrice ImNivGris(tImage Im){
    return(Im->NivGris);

}

tImage ImLire(char NomFichier[]){
    // 1 ouvre
    FILE *f;
    f=fopen("NomFichier.txt","rt");
    int nbcol;
    int nblign;
    fscanf(f,"P2 %d" "%d",&nbcol,nblign);
    tImage image = ImAllouer(nblign,nbcol);
    
    // nbr col lign
    // nv image 
    // v-lire valeur pixel 
    // mettre dans m gris 
    // 
}

void ImEcrire(tImage Im, char NomFichier[]){


}