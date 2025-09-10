#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calendrier.h"
#include "evenement.h"
#include "date.h"


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




int AjouterEvenement(tCalendrier* pCalendrier, tEvenement evenement) {
    /* on associe un nv calendrier a celui qui est pointé par pCalendrier*/

     /* le calendrier est vide */
    if((*pCalendrier)==NULL){
        tCalendrier nvCal = malloc(sizeof(struct sCalendrier));
        nvCal->pEvenement = evenement;
        nvCal->pSuivant = NULL;

        /* vu que *pCalendrier est null il faut le faire pointer sur le le nv calendrier*/
        *pCalendrier=nvCal;
        
        return 1;
    }

    tCalendrier actuel = *pCalendrier;
    /* ici on verifie que le calendrier pointer par pCalendrier peut accepter notre event */
    while(actuel!=NULL){
        
        /* verif des du nom du calendrier actuel a celui donné*/
        if((Titre((actuel)->pEvenement))==(Titre(evenement)) ){
            return -1;
         }
        /* verif que les dates soient dispo */
        if((Chevauche(Debut(evenement),Fin(evenement),
        Debut(actuel->pEvenement),Fin(actuel->pEvenement))==1)){
        
            return -1;
        }        
        /* on pointe l'evenement d'apres*/
    
        actuel=actuel->pSuivant;
    }

   
    
    /* normalement actuel pointe sur le  calendrier avec un nULL en psuivant */
    tCalendrier nouvCal = malloc(sizeof(struct sCalendrier));
    if(nouvCal==NULL){
        return -1;
    }
    actuel = *pCalendrier;
    nouvCal->pEvenement=evenement;
    nouvCal->pSuivant=NULL;
    while(actuel->pSuivant!=NULL){
        actuel=actuel->pSuivant;
        
    }
    actuel->pSuivant=nouvCal;

    return 1;


}

tEvenement PremierEvenement(tCalendrier calendrier) {
    return calendrier->pEvenement;
}

tCalendrier SuiteDuCalendrier(tCalendrier calendrier) {
    return calendrier->pSuivant;
}

void DetruitCalendrier(tCalendrier* calendrier) {
   if((*calendrier)->pSuivant!=NULL && *calendrier!=NULL){
    /* on pointe le calendrier */
        tCalendrier actuel = *calendrier;
        while(actuel!=NULL){
            /* on pointe le cal d'apres */
            tCalendrier suivant = actuel->pSuivant;
            /* on detruit l'evenement correspondant */
            DetruitEvenement(&(actuel->pEvenement));
            /* on free actuel */
            free(actuel);
            /* on passe a celui d'apres en actualisant actuel avec celui d'apres*/
            actuel = suivant;
        }
        /* il ne reste plus qu'a rendre notre pointeur originel */
        *calendrier = NULL;
        }

   }
            
void AfficheCalendrier(tCalendrier calendrier) {
    /* verif pointeur vide */
    if((calendrier)==NULL){
        printf("Calendrier vide");
        return;
    }
    tCalendrier actuel = calendrier;
    while(actuel!=NULL){
        AfficheEvenement(actuel->pEvenement);
        actuel=actuel->pSuivant;
    }

}

int SupprimeEvenementsPeriode(tCalendrier* pCalendrier, struct sDate debut, struct sDate fin) {
    int nbrElemsupp = 0;
    
    if (pCalendrier == NULL || *pCalendrier == NULL) {
        return nbrElemsupp;
    }

    while((*pCalendrier)->pSuivant != NULL){
        tCalendrier suiv = (*pCalendrier);
        *pCalendrier=(*pCalendrier)->pSuivant;
            if(Chevauche(debut,fin,Debut((*pCalendrier)->pEvenement)
            ,Debut((*pCalendrier)->pEvenement))==1){
                DetruitEvenement(&((suiv)->pEvenement));
                nbrElemsupp ++;
        }
}

        return nbrElemsupp;

}

    





int ExportCalendrier(tCalendrier calendrier, const char* fichier) {
    
    FILE* f= fopen(fichier ,"w");
    if(f==NULL){
        return 1;
    }

    fprintf(f, "BEGIN:VCALENDAR\nVERSION:2.0\n");
    
    tCalendrier courant = calendrier;
    char dateDebut[15], dateFin[15];  // 14 caractères + \0
    
    while (courant != NULL) {
        YYYYMMDDTHHMM(dateDebut, Debut(courant->pEvenement));
        YYYYMMDDTHHMM(dateFin, Fin(courant->pEvenement));
        
        // Ajout de "00" pour les secondes dans le format iCal
        fprintf(f, "BEGIN:VEVENT\n");
        fprintf(f, "SUMMARY:%s\n", Titre(courant->pEvenement));
        fprintf(f, "DTSTART:%s00\n", dateDebut);
        fprintf(f, "DTEND:%s00\n", dateFin);
        fprintf(f, "END:VEVENT\n");
        
        courant = courant->pSuivant;
    }
    
    fprintf(f, "END:VCALENDAR\n");
    fclose(f);
    return 0;

}

    