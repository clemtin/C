#include <stdio.h>


void scdtohms(int sec){
    int heure = sec / 3600; 
    int min = (sec % 3600) / 60; 
    int seconde = sec % 60; 

    printf("%d secondes = %d heures, %d minutes, %d secondes\n", sec, heure, min, seconde);
    
}

void tabscd(int sec, int tab[]){
    int heure = sec / 3600; 
    int min = (sec % 3600) / 60; 
    int seconde = sec % 60; 
    tab[0] = heure;
    tab[1] = min;
    tab[2] = seconde;
    for(int i=0;i<3;i++){
        printf("%d ",tab[i]);
    }
 
}

int main(void){
    int sec = 6000;
    int tab[3];
    scdtohms(sec);

    tabscd(sec,tab);
}