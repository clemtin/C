#include <stdio.h>





int main(void){


char x;
    int lettres = 0 ,compteur = 0;
    scanf("%c",&x);
    while(x!='#'){
        if(x=='a'||x=='e'||x=='i'
        ||x=='o'||x=='u'||x=='y'){
            compteur++;
        }
        x++;


    }
    printf("nbr voyelles %d\n",compteur);

    return 0;
}