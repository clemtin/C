#ifndef LISTEMOT_H
#define LISTEMOT_H

#include <stdio.h>






// Mot d'un texte
struct sMot {
    char *mot; //chaine de cara alloué dynamiquement
    int taille; //nbr de cara du mot
    int occurences; // nbr d'occu du mot dans un texte
    struct sMot *suivant; //mot suivant dans le contexte d'une liste chainé 

    };

// Liste de mots

struct sListeMots {
    struct sMot *debut;
    struct sMot *fin;
    int nbMots;

    };


typedef struct sListeMots *tListeMots;

extern tListeMots creerListeMots();
extern void detruireListeMots(tListeMots liste);
extern int nombreDeMot(tListeMots liste);
extern void ajouterMotAvecOcc(tListeMots liste, char *mot, int nbOcc);
extern void ajouterMot(tListeMots liste,char *mot);
extern void ecrireListeMots(tListeMots liste, FILE *fich);
extern void ajouterOccurrenceMot(tListeMots liste, char *mot);
extern void ecrireCsvListeMots(tListeMots liste, char *nomFichier);
extern void supprimerPetitsMots(tListeMots liste, int tailleMin);

#endif/*LISTEMOT_H*/


