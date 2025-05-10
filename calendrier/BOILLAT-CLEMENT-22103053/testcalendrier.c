#include <stdio.h>
#include <stdlib.h>
#include "calendrier.h"
#include "evenement.h"
#include "date.h"

int main() {
    tCalendrier cal = NULL;
    struct sDate d1 = {2024, 10, 1, 8, 0};
    struct sDate f1 = {2024, 10, 1, 8, 59};
    struct sDate d2 = {2024, 10, 1, 9, 0};
    struct sDate f2 = {2024, 10, 1, 9, 59};
    
    // Test calendrier vide
    printf("Test calendrier vide:\n");
    AfficheCalendrier(cal);
    
    // Test ajout d'événements
    printf("\nTest ajout d'événements:\n");
    tEvenement evt1 = CreerEvenement("Test1", d1, f1);
    tEvenement evt2 = CreerEvenement("Test2", d2, f2);
    
    printf("Ajout evt1: %d\n", AjouterEvenement(&cal, evt1));
    printf("Ajout evt2: %d\n", AjouterEvenement(&cal, evt2));
    
    printf("\nContenu du calendrier:\n");
    AfficheCalendrier(cal);
    
    // Test export
    printf("\nTest export du calendrier:\n");
    printf("Export: %d\n", ExportCalendrier(cal, "test_calendar.ics"));
     

    // Test suppression par période
    struct sDate debut_sup = {2024, 10, 1, 8, 30};
    struct sDate fin_sup = {2024, 11, 1, 9, 30};
    printf("\nTest suppression période (8h30-9h30):\n");
    int nb = SupprimeEvenementsPeriode(&cal, debut_sup, fin_sup);
    printf("Nombre d'événements supprimés: %d\n", nb);
    printf("\nCalendrier après suppression:\n");
    AfficheCalendrier(cal);
    
    // Nettoyage
    DetruitCalendrier(&cal);
    
    return 0;

}