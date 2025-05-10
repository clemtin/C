#include <stdio.h>


void anneebissex(){
    int x = 0;
    printf("Choisie une année\n ");
    scanf("%d",&x);
    if(x%4==0 && x%100!=0){
        printf("pas bissextille");
    }
    else{
        printf("bissextille");
    }
}

void ex2(){
    char x;
    int compteur = 0;
    scanf("%c",&x);
    while(x!='#'){
        if(x=='a'||x=='e'||x=='i'
        ||x=='o'||x=='u'||x=='y'){
            compteur++;
        }
        x++;


    }
    printf("nbr voyelles %d\n",compteur);
}

void ex3(){
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

}



void ex4(){
    int nbr_ligne = 0;
    int etoiles = 1;
    printf("nbr ligne ?\n");
    scanf("%d",&nbr_ligne);
    
        for(nbr_ligne;nbr_ligne>0;nbr_ligne--){    
        for(int i=0;i<nbr_ligne-1;i++){
            printf(" ");

        }
        
        for(int i =0;i<etoiles;i++){
                printf("*");
            }
    
            printf("\n");
            etoiles=etoiles+2;
        }
        

    }

void ex5(){
    int max = 0;
    printf("max de table \n");
    scanf("%d",&max);
    while(max>18 || max<0){
        scanf("%d",&max);
    }
    for(int i = 0;i<max;i++){
        printf("%d",i);

    }
    printf("\n");
    for(int i = 0; i <= max; i++) {
        printf("---");
}
}

int main(void){
/*   printf("ex1 \n");
    ex1();
    printf("ex2 \n");
    ex2();
    printf("ex3 \n");
    ex3();
    printf("ex4 \n");
    ex4();*/
    printf("ex5 \n");
    ex5();




    return 0;
}