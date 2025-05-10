#include <stdio.h>
#include <stdlib.h>
#include "identite.h"

int main(void) {
    // Création d'une identité
    tIdentite identite = IdentiteCreer(3, "Boillat", "Clement", 'M', "19/01/2003");
    
    if (identite == NULL) {
        printf("Erreur de création d'identité.\n");
        return 1;
    }

    // Affichage de l'identité
    IdentiteAfficher(identite);

    // Test des accesseurs
    printf("Identifiant : %d\n", IdentiteIdentifiant(identite));
    printf("Nom         : %s\n", IdentiteNom(identite));
    printf("Prenom      : %s\n", IdentitePrenom(identite));
    printf("Sexe        : %c\n", IdentiteSexe(identite));
    printf("DateNaiss   : %s\n", IdentiteDateNaissance(identite));

    // Libération de la mémoire
    IdentiteLiberer(identite);



    FILE *f = fopen("personne.ind","r");
    tIdentite id = IdentiteLiref(f);
    IdentiteAfficher(id);
    IdentiteLiberer(id);

    return 0;
}
