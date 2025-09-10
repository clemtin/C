#include <stdio.h>
#include <string.h>
#include <stdbool.h>


bool areAlmostEqual(char* s1, char* s2) {
    int nbr_caradiff = 0;
    int longueur = strlen(s1);
        for (int i = 0; i < longueur; i++) {
                if(s1[i] != s2[i]){
                    nbr_caradiff++;
                }
            
        }
        return (nbr_caradiff<=1);
}

int main(void){
    char s1[] = "bank";
    char s2[] = "kanb";

    printf("%d\n",areAlmostEqual(s1,s2));
    return 0;
}