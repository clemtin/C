#include <stdio.h>

#define MAX 80


int main(void){
    char c;
    char chaine[MAX];
    char chaine2[MAX];
    char chaine3[MAX];
    int i = 0;
    scanf("%c",&c);
    

    while(c!='\n' && i<MAX){
        chaine[i]=c;
        scanf("%c",&c);
        i++;
        
    }
    chaine[i]='\0';

    printf("%s,nbr cara %d \n",chaine,i);

    int j=0;
    int a=i-1;


    for(a;a>=0;a--){
        chaine2[j]=chaine3[a];

        j++;
    }
    chaine2[j]='\0';
    printf("%s\n",chaine2);


    while(i<j){
        

        }
    




    return 0;
    }


