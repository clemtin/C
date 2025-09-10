#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"


typedef unsigned char **tMatrice;


tMatrice MatAllouer(int Nblig, int NbCol){
    tMatrice tab = malloc(Nblig*(sizeof(char*))); //tableau de pointeur de char
    unsigned char* mat = malloc(NbCol * Nblig *(sizeof(unsigned char))); // char* car tableau de char et pas seulement un char

    if(tab==NULL){
        return NULL;
    }
    if(mat==NULL){
        return NULL;
    }

    for(int i=0;i<Nblig;i++){
        tab[i]=&((mat[i*NbCol]));
    }

    return tab;
}


tMatrice MatLire(int *pNbLig, int *pNbCol){
    printf("Nbr ligne \n");
    scanf("%d",pNbLig);
    printf("Nbr colone \n");
    scanf("%d",pNbCol);

    tMatrice x=MatAllouer(*pNbLig,*pNbCol);

    for(int i=0;i<*pNbLig;i++){
        for(int j=0;j<*pNbCol;j++){
            scanf("%hhu",&(x[i][j]));
            printf("ij = %d %d = %hhu \n",i,j,x[i][j]);
        }
    }
    printf("nb ligne = %d nb col =%d \n",*pNbLig,*pNbCol);
    return x;
}



void MatAfficher(tMatrice Mat, int NbLig, int NbCol){
    for(int i=0;i<NbLig;i++){
        for(int j=0;j<NbCol;j++){
            printf("ij = %d %d = % \n",i,j,&(Mat[i][j]));
        }
    }
}

tMatrice MatCopier(tMatrice Mat, int Nblig, int NbCol){
    unsigned char* nvMat= malloc(Nblig*NbCol*(sizeof(char*)));
    if(nvMat == NULL){
        return NULL;
    }
    for(int i=0;i<Nblig;i++){
        for(int j=0;j<NbCol;j++){
            nvMat[i+j]=Mat[i][j];
        }
    }
    return &nvMat;
}
void MatLiberer(tMatrice *pMat) {
    if (*pMat != NULL) {
        // Free individual rows
        for (int i = 0; i < (*pMat)[0]; i++) {
            free((*pMat)[i]);
        }
        free(*pMat);
        *pMat = NULL;
    }
}