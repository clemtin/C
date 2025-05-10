#include <stdio.h>

#define MAX 100

void ex1(void){
    int nbr = 0;
    printf("choissez la longueur du tab\n");
    scanf("%d",&nbr);
    int tab[MAX];
    float moy = 0;
    printf("choissiez les valeurs");
    for(int i =0;i<nbr;i++){
        scanf("%d",&tab[i]);
        moy += tab[i];
    }
    moy = moy/nbr;
    printf("moy = %.2f\n",moy);

    for(int i =0;i<nbr;i++){
        if(tab[i]>moy){
            printf("%d, ",tab[i]);
        }
    }
    printf("\n");
}

int main(void){
    ex1();

    return 0;
}