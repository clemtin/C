#include <stdio.h>


int main(void){
     int nbrvaleur;
    float moyenne = 0;
    printf("entrer nbr valeur\n");
    scanf("%d",&nbrvaleur);
    int tab[nbrvaleur];
    for(int i=0;i<nbrvaleur;i++){
        printf("Choissiez une valeur\n");
        scanf("%d",&tab[i]);
        moyenne += tab[i];
    }
    moyenne = moyenne/nbrvaleur;
    printf("%.2f\n",moyenne);
    return 0;
}

    