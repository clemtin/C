#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listemots.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <nom_fichier> <taille_min_mots>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Récupérer les arguments
    char *nomFichier = argv[1];
    int tailleMinMots = atoi(argv[2]);

    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return EXIT_FAILURE;
    }

    // Initialisation de la liste de mots
    tListeMots listeMots = creerListeMots();

    int c;
    char motCourant[100]; // Taille maximale du mot
    int indexMot = 0;
    while ((c = fgetc(fichier)) != EOF) {
        if (caractereDunMot((unsigned char)c)) {
            motCourant[indexMot++] = c;
        } else if (indexMot > 0) {
            motCourant[indexMot] = '\0'; // Terminer le mot avec un null terminator
            ajouterMotAvecOcc(listeMots, motCourant, 1);
            indexMot = 0;
        }
    }

    fclose(fichier);

    // Écriture de la liste complète des mots avec leurs occurrences dans liste_mots_01.txt
    ecrireCsvListeMots(listeMots, "liste_mots_01.txt");

    // Suppression des mots de taille inférieure à tailleMinMots
    supprimerPetitsMots(listeMots, tailleMinMots);

    // Écriture des mots restants dans liste_mots_02.txt
    ecrireCsvListeMots(listeMots, "liste_mots_02.txt");

    // Libération de la mémoire
    detruireListeMots(listeMots);

    return EXIT_SUCCESS;
}
