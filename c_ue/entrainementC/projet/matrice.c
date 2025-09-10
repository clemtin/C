#include <stdio.h>


int matrice[3][3] = {
    //  0,0 0,1 0,2
        {1, 2, 3},
    //  1,0 
        {4, 5, 6},
    //  2,0
        {7, 8, 9}
    };


void typecara(void){
    char a;
    scanf("%c",&a);

    printf("valeur asci %d\n",a);
    printf("valeur en memoire %d\n",&a);


    if(a >= 'a' && a <= 'z'){
        printf("L'entré est une lettre minuscule\n");
    }
    else if(a>='A' && a<='Z'){
        printf("l'entrée est une lettre majuscule\n");
    }
    else if(a>='1' && a<='9'){
        printf("l'entrée est un chiffre\n");
    }
    else{
        printf("L'entrée est autre chose\n");
    }
}

void calculerCOlmat_moyenne(int matrice[3][3]){
    int tab [3] = {0,0,0};
    int ligne = 3;
    int col = 3;
    for(int i=0;i<ligne;i++){
        for(int j=0;j<col;j++){
            tab[j] += matrice[i][j];
        }

    } 
    for(int a=0;a<3;a++){
        // attention a bien utilisé / et pas % 
        tab[a]=tab[a]/3;
        printf("%d\n",tab[a]);
    }
}
    



int main(void){
    
    typecara();
    calculerCOlmat_moyenne(matrice);
    return 0;
}