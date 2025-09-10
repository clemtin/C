#include <stdio.h>

int main(void){
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
        

    

    return 0;
    }