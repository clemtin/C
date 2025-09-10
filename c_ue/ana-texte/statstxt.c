#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listemots.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <nom_fichier>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fichier = fopen(argv[1], "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return EXIT_FAILURE;
    }

// Initialisation des statistiques
    int nb_phrases = 0;
    int nb_mots = 0;
    int nb_caracteres = 0;
    int longueur_max_phrase = 0;
    int longueur_phrase_actuelle = 0;
    tListeMots phrase_la_plus_longue = creerListeMots();
    tListeMots phrase_actu = creerListeMots();
    int c;


    while ((c = fgetc(fichier)) != EOF) {
        ajouterMot(phrase_actu, &c);
        if (caractereDunMot((unsigned char)c) == 1) {
            nb_caracteres++;
            longueur_phrase_actuelle++;
            
        }
        if (c == ' ') {
            nb_mots++;
        }
        if (caractereFinDePhrase((unsigned char)c) == 1) {
            nb_phrases++;
            // Mettre à jour la longueur maximale de la phrase
            if (longueur_phrase_actuelle > longueur_max_phrase) {
                longueur_max_phrase = longueur_phrase_actuelle;
                // Mettre à jour la phrase la plus longue
                detruireListeMots(phrase_la_plus_longue);
                phrase_la_plus_longue = phrase_actu;
            } else {
                // Si la phrase actuelle n'est pas la plus longue, la libérer
                detruireListeMots(phrase_actu);
             }
                // Réinitialiser la phrase actuelle
                phrase_actu = creerListeMots();
                longueur_phrase_actuelle = 0;
            }
        }


    fclose(fichier);

    // Calcul de la longueur moyenne d'un mot
    double longueur_moyenne_mot = (double)nb_caracteres / nb_mots;

    // Calcul de la longueur moyenne d'une phrase
    double longueur_moyenne_phrase = (double)nb_mots / nb_phrases;


    // Affichage des statistiques
    printf("Texte : %s\n", argv[1]);
    printf("Nombre de phrases : %d\n", nb_phrases);
    printf("Nombre de mots : %d\n", nb_mots);
    printf("Nombre de caracteres : %d\n", nb_caracteres);
    printf("Longueur moyenne d'un mot : %.2f\n", longueur_moyenne_mot);
    printf("Longueur moyenne d'une phrase : %.2f\n", longueur_moyenne_phrase);
    printf("Phrase la plus longue (%d mots) : ", longueur_max_phrase);
    ecrireListeMots(phrase_la_plus_longue, stdout);

    // Écriture des statistiques dans le fichier statistiques.txt
    FILE *statistiques = fopen("statistiques.txt", "w");
    if (statistiques == NULL) {
        printf("Impossible d'écrire dans le fichier statistiques.txt\n");
        return EXIT_FAILURE;
    }
    fprintf(statistiques, "Texte : %s\n", argv[1]);
    fprintf(statistiques, "Nombre de phrases : %d\n", nb_phrases);
    fprintf(statistiques, "Nombre de mots : %d\n", nb_mots);
    fprintf(statistiques, "Nombre de caracteres : %d\n", nb_caracteres);
    fprintf(statistiques, "Longueur moyenne d'un mot : %.2f\n", longueur_moyenne_mot);
    fprintf(statistiques, "Longueur moyenne d'une phrase : %.2f\n", longueur_moyenne_phrase);
    fprintf(statistiques, "Phrase la plus longue (%d mots) : ", longueur_max_phrase);
    ecrireListeMots(phrase_la_plus_longue, statistiques);
    fclose(statistiques);

    // Nettoyage
    fclose(fichier);
    detruireListeMots(phrase_la_plus_longue);
    return EXIT_SUCCESS;
}
