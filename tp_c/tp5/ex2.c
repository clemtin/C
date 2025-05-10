#include <stdio.h>
#include <stdlib.h>

double *CreerTableau(int Nbelts){

    double *tab = malloc(Nbelts * sizeof(double));
    if(tab==NULL){
        return NULL;
    }
    return tab;
}


void SaisirTableau(double *Tab, int NbElts){
    for(int i=0;i<NbElts;i++){
        printf("Entrez l'elem %d : \n",i);
        scanf("%lf", &Tab[i]);
    }


}


void AfficherTableau(double *Tab, int Nbelts){
    for(int i=0;i<Nbelts;i++){
        printf("%lf",Tab[i]);
    }

}


void LibererTableau(double *Tab){
    free(Tab);
}