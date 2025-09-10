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
            printf("ij = %d %d = %d \n",i,j,&(Mat[i][j]));
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
}

int main(void){
    int nbLig;
    int nBCol;
    int* pNblig = &nbLig;
    int* pNbCol = &nBCol;

    printf("compile \n");
    MatLire(pNblig,pNbCol);


    tMatrice mat = MatAllouer(2,2);
    MatAfficher(mat,2,2);
}




int main(void) {
    int NbLig, NbCol;

    tMatrice mat = MatLire(&NbLig, &NbCol);

    printf("Matrix with %d rows and %d columns has been successfully created.\n", NbLig, NbCol);
    printf("Original Matrix:\n");
    MatAfficher(mat, NbLig, NbCol);

    tMatrice copy = MatCopier(mat, NbLig, NbCol);

    printf("Copy of the Matrix:\n");
    MatAfficher(copy, NbLig, NbCol);

    MatLiberer(&copy); 
    MatLiberer(&mat);
    return 0;
}