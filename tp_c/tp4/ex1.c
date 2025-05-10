#include <stdio.h>



void afficherTab(int Tab[],int NbElt){
    for(int i =0;i<NbElt;i++){
        printf("%d ",Tab[i]);
    }
    printf("\n");

}


int Min(int Tab[], int NbElt){
    int min = Tab[0];
    for (int i=1;i<NbElt;i++){
        if(Tab[i]<min){
            min = Tab[i];
        }
    }
    return min;
}




int Max(int Tab[], int NbElt){
    int max = Tab[0];
    for (int i=1;i<NbElt;i++){
        if(Tab[i]>max){
            max = Tab[i];
        }
    }
    return max;
}


void MinMAx(int Tab[], int NbElt, int *pMin, int *pMax){
    *pMin = Min(Tab,NbElt);
    *pMax = Max(Tab,NbElt);
    printf("Min = %d ,Max = %d \n",*pMin,*pMax);
}

void MinMax2(int Tab[], int NbElt, int *pMin, int *pMax){

}

int SupprimerVal(int Tab[],int *pNbElt, int Val){
    int a=0;
    int supp = 0;
    int Tab2[*pNbElt];
    for(int i=0;i<*pNbElt;i++){

        if(Tab[i]==Val){
            i++;
            supp++;
        }
        Tab2[a]=Tab[i];
        a++;
    }
    *pNbElt=a;

    for(int i=0;i<*pNbElt;i++){
        printf("%d ",Tab2[i]);
    }
    printf("\n");
    return supp;
}

int main(void){
    int tab[10] = {1,5,6,76,800,5,42,19,27,23};
    int nbelem = 10;
    int min = tab[0];
    int max = tab[0];
    int *pMin = &min;
    int *pMax = &max;
    int *pNbelt = &nbelem;
    afficherTab(tab,nbelem);
    Min(tab,nbelem);
    Max(tab,nbelem);
    MinMAx(tab,nbelem,pMin,pMax);
    SupprimerVal(tab,pNbelt,5);

    return 0;
}