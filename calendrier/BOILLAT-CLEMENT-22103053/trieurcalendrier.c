#include "calendrier.h"
#include "date.h"
#include "evenement.h"
#include <stdlib.h>
#include <stdio.h>

/* permet de pointer un sEvenment*/
typedef struct sEvenement* tEvenement;

/* permet de pointer un sCalendrier*/
typedef struct sCalendrier* tCalendrier;

/* creer un type date rapidement*/
typedef const struct sDate dated;

struct sCalendrier {
    tEvenement pEvenement;
    tCalendrier pSuivant;

};




static int CompareEvents(const void* pa, const void* pb) {
    
    tEvenement event1 = *(tEvenement*)pa;
    tEvenement event2 = *(tEvenement*)pb;

    
    dated date1 = Debut(event1);
    dated date2 = Debut(event2);

    
    return Compare(date1, date2);
}



void TriCalendrier(tCalendrier calendrier){
    int compt = 0;
    tCalendrier actuel = calendrier;
    while(actuel!=NULL){
        compt++;
        actuel = actuel->pSuivant;
    }

    tEvenement* tabEvent = malloc(compt * sizeof(tEvenement));
    if(tabEvent == NULL){
        return;
    }

    actuel = calendrier;
    for(int i = 0;i<compt;i++){
        tabEvent[i] = actuel->pEvenement;
        actuel = actuel->pSuivant;
    }

    



    qsort(tabEvent,compt,sizeof(tEvenement),&CompareEvents);

    actuel = calendrier;
    for(int i = 0; i<compt;i++){
        actuel->pEvenement = tabEvent[i];
        actuel=actuel->pSuivant;
    }

    free(tabEvent);

}