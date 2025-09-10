#include <stdio.h>
#include <stdlib.h>
#include "listemots.h"
#include <string.h>

static struct sMot *motCreer(char *mot, int occ){
    struct sMot *nouveauMot = (struct sMot*)malloc(sizeof(struct sMot));
    if (nouveauMot == NULL){
        return NULL;
    }
    
    nouveauMot->mot = strdup(mot);
    if(nouveauMot->mot == NULL){
        free(nouveauMot);
        return NULL;
    }


    nouveauMot->taille= strlen(mot);
    nouveauMot->occurences = occ;
    nouveauMot->suivant = NULL;

    return nouveauMot;
}


static void motLiberer(struct sMot *mot){
    if(mot != NULL){
        free(mot->mot);
        
    }
    free(mot);
}



tListeMots creerListeMots() {
    tListeMots nvListe = malloc(sizeof(struct sListeMots)); // Allocation pour la structure, pas pour le pointeur
    if (nvListe == NULL) {
        return NULL;
    }

    nvListe->debut = NULL;
    nvListe->fin = NULL;
    nvListe->nbMots = 0;

    return nvListe;
}


void detruireListeMots(tListeMots liste) {
    if (liste != NULL) {
        struct sMot *actu = liste->debut;
        struct sMot *suivant;
        while (actu != NULL) {
            suivant = actu->suivant;
            motLiberer(actu);
            actu = suivant;
        }
        liste->nbMots=0;
        free(liste);
    }
}




int nombreDeMot(tListeMots liste){
    if(liste == NULL){
        return 0;
    }
    printf("%d", liste->nbMots);
    return liste->nbMots;

}


void ajouterMotAvecOcc(tListeMots liste, char *mot, int nbOcc){
    struct sMot *nouveauMot = motCreer(mot, nbOcc );

    if(liste == NULL){

    }
      if (liste->debut == NULL) {
        liste->debut = nouveauMot;
    } else {
        liste->fin->suivant = nouveauMot;
    }
    liste->fin = nouveauMot;
    liste->nbMots++;
}


void ajouterMot(tListeMots liste, char *mot){
    ajouterMotAvecOcc(liste, mot, 1);

}


void ecrireListeMots(tListeMots liste, FILE *fich) {
    if (liste == NULL || fich == NULL) {
        return;
    }

    struct sMot *courant = liste->debut;
    while (courant != NULL) {
        fprintf(fich, "%s ", courant->mot);
        courant = courant->suivant;
    }
    fprintf(fich, "\n");
}


void ajouterOccurrenceMot(tListeMots liste, char *mot) {
    if (liste == NULL || mot == NULL) {
        return;
    }

    struct sMot *courant = liste->debut;
    while (courant != NULL) {
        if (strcmp(courant->mot, mot) == 0) {
            courant->occurences++;
            return;
        }
        courant = courant->suivant;
    }

    // Si le mot n'est pas trouvé, l'ajouter avec une occurrence de 1
    ajouterMot(liste, mot);
}


void ecrireCsvListeMots(tListeMots liste, char *nomFichier) {
    if (liste == NULL || nomFichier == NULL) {
        return;
    }

    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    struct sMot *courant = liste->debut;
    while (courant != NULL) {
        fprintf(fichier, "%s, %d, %d\n", courant->mot, courant->taille, courant->occurences);
        courant = courant->suivant;
    }

    fclose(fichier);
}



void supprimerPetitsMots(tListeMots liste, int tailleMin) {
    if (liste == NULL) {
        return;
    }

    struct sMot *actuel = liste->debut;
    struct sMot *precedent = NULL;

    while (actuel != NULL) {
        if (actuel->taille < tailleMin) {
            if (precedent == NULL) {
                // Le mot à supprimer est en tête de liste
                liste->debut = actuel->suivant;
            } else {
                // Le mot à supprimer n'est pas en tête de liste
                precedent->suivant = actuel->suivant;
            }

            // Libérer la mémoire du mot supprimé
            motLiberer(actuel);

            // Mettre à jour le nombre de mots dans la liste
            liste->nbMots--;

            // Passer au mot suivant
            actuel = (precedent == NULL) ? liste->debut : precedent->suivant;
        } else {
            // Passer au mot suivant
            precedent = actuel;
            actuel = actuel->suivant;
        }
    }

    // Mettre à jour le pointeur de fin de liste si nécessaire
    if (precedent != NULL) {
        liste->fin = precedent;
    }
}
