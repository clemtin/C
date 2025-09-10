#include "calendrier.h"
#include "date.h"
#include "evenement.h"
#include "trieurcalendrier.h"
#include <stdio.h>
#include <stdlib.h>

/* permet de pointer un sEvenment*/
typedef struct sEvenement* tEvenement;

/* permet de pointer un sCalendrier*/
typedef struct sCalendrier* tCalendrier;

/* creer un type date rapidement*/
typedef const struct sDate dated;

int main(void) {
    // Créer un calendrier de test
    tCalendrier calendrier = NULL;
    
    // Création de quelques événements avec des dates différentes
    dated date0 = {2024,10,5,10,10};
    dated date1 = {2024,10,6,20,40}; 
    dated date2 = {2024,1,10,19,19};
    dated date2bis = {2024,1,11,10,59};
    dated date3 = {2024,2,20,8,0};
    dated date3bis = {2024,2,20,9,0};
    
    


    tEvenement event1 = CreerEvenement("Réunion",date0,date1);

    tEvenement event2 = CreerEvenement("Anniversaire",date2,date2bis);
    tEvenement event3 = CreerEvenement("Conférence", date3,date3bis);
    
    // Ajouter les événements au calendrier

    printf("Ajout evt1: %d\n", AjouterEvenement(&calendrier, event1));
    printf("Ajout evt2: %d\n", AjouterEvenement(&calendrier, event2));
    printf("Ajout evt3: %d\n", AjouterEvenement(&calendrier, event3));


    // Afficher le calendrier avant tri
    printf("Calendrier avant tri :\n");
    AfficheCalendrier(calendrier);
    
    // Trier le calendrier
    TriCalendrier(calendrier);
    
    // Afficher le calendrier après tri
    printf("\nCalendrier après tri :\n");
    AfficheCalendrier(calendrier);
    
    // Libérer la mémoire
    DetruitCalendrier(&calendrier);
    
    return 0;
}