#include "genea.h"

    // Arbre géné alogique
struct sArbre{
    struct sFiche * pPremiere ; // Adresse de la première fiche
    struct sFiche * pDerniere ; // Adresse de la dernière fiche
        };


        // Fiche associée à chaque individu présent dans l’arbre
struct sFiche{
    tIdentite Identite ; // Acc ès aux informations de l’identit é de la personne
    struct sFiche * pPere ; // Adresse de la fiche du père
    struct sFiche * pMere ; // Adresse de la fiche de la mère
    struct sFiche * pSuivante ; // Adresse de la fiche suivante
    };

tArbre ArbreCreer(void){
    tArbre arbre = malloc(sizeof(struct sArbre));
    if (arbre == NULL) {
        return NULL;
    }
    arbre->pPremiere = NULL;
    arbre->pDerniere = NULL;
    return arbre;
    } 
   
void ArbreAfficher(tArbre Arbre){
    struct sFiche *courant = Arbre->pPremiere;
    while (courant != NULL) {
        IdentiteAfficher(courant->Identite);
        courant = courant->pSuivante;
    }
}

void ArbreAjouterPersonne(tArbre Arbre, tIdentite Identite){
    struct sFiche *nouvelleFiche = malloc(sizeof(struct sFiche));
    if (nouvelleFiche == NULL) {
        return;
    }
    nouvelleFiche->Identite = Identite;
    nouvelleFiche->pPere = NULL;
    nouvelleFiche->pMere = NULL;
    nouvelleFiche->pSuivante = NULL;

    if (Arbre->pPremiere == NULL) {
        Arbre->pPremiere = nouvelleFiche;
        Arbre->pDerniere = nouvelleFiche;
    } else {
        Arbre->pDerniere->pSuivante = nouvelleFiche;
        Arbre->pDerniere = nouvelleFiche;
    }
}


void ArbreLiberer(tArbre Arbre){
    struct sFiche *courant = Arbre->pPremiere;
    while (courant != NULL) {
        struct sFiche *suivante = courant->pSuivante;
        IdentiteLiberer(courant->Identite);
        free(courant);
        courant = suivante;
    }
    free(Arbre);
}

tArbre ArbreLirePersonnesFichier(char Fichier[]){
    FILE *f = fopen(Fichier, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s.\n", Fichier);
        return NULL;
    }
    tArbre arbre = ArbreCreer();
    if (arbre == NULL) {
        fclose(f);
        return NULL;
    }
    // Lire chaque personne depuis le fichier et les ajouter à l'arbre
    while (1) {
        tIdentite nouvelleIdentite = IdentiteLiref(f);
        if (nouvelleIdentite == NULL) {
            break;
        }
        ArbreAjouterPersonne(arbre, nouvelleIdentite);
    }

    fclose(f);
    return arbre;
}

void ArbreAjouterLienParente(tArbre Arbre, int IdEnfant, int IdParent, char Parente){

        struct sFiche *enfant = NULL;
        struct sFiche *parent = NULL;
    
        // Commencer au début de l'arbre, chercher l'enfant
        struct sFiche *current = Arbre->pPremiere;
        while (current != NULL) {
            if (IdentiteIdentifiant(current->Identite) == IdEnfant) {
                enfant = current;
                break;
            }
            current = current->pSuivante;
        }
    
        // Recommencer au début de l'arbre, chercher le parent
        current = Arbre->pPremiere;
        while (current != NULL) {
            if (IdentiteIdentifiant(current->Identite) == IdParent) {
                parent = current;
                break;
            }
            current = current->pSuivante;
        }
    
        // Vérifier si les identifiants sont trouvés
        if (enfant == NULL || parent == NULL) {
            fprintf(stderr, "Erreur : Identifiant non trouve dans l'arbre.\n");
            return;
        }
    
        // Établir le lien de parenté en fonction du type de parenté
        if (Parente == 'P') {
            enfant->pPere = parent;
        } else if (Parente == 'M') {
            enfant->pMere = parent;
        } else {
            fprintf(stderr, "Erreur : Type de parente non valide.\n");
        }
    }


int ArbreLireLienParentef(FILE *f, int *pIdEnfant, int *pIdParent, char *pParente){
    if (fscanf(f, "%d %d %c", pIdEnfant, pIdParent, pParente) == 3) {
        return 1; // La lecture s'est bien passée
    } else {
        return 0;
    }
}

tArbre ArbreLireLienParenteFichier(tArbre Arbre, char Fichier[]) {
    FILE *f = fopen(Fichier, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s.\n", Fichier);
        return NULL;
    }

    int idEnfant, idParent;
    char parente;

    // Lire les liens de parenté à partir du fichier
    while (ArbreLireLienParentef(f, &idEnfant, &idParent, &parente)) {
        // Ajouter le lien de parenté à l'arbre
        ArbreAjouterLienParente(Arbre, idEnfant, idParent, parente);
    }

    fclose(f);
    return Arbre;
}

//p3
void ArbreEcrireGV(tArbre Arbre, char Fichier[]) {
    FILE *f = fopen(Fichier, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s pour écriture.\n", Fichier);
        return;
    }

    // Écriture de l'en-tête DOT
    fprintf(f, "digraph {\n");
    fprintf(f, "\trankdir = \"BT\";\n");

    // Écriture des styles des nœuds et la couleur pour les hommes
    fprintf(f, "\n\tnode [shape = box, color = red, fontname = \"Arial\", fontsize = 10];\n");

    // Parcourir l'arbre pour écrire les nœuds pour les hommes
    struct sFiche* current = Arbre->pPremiere;
    while (current != NULL) {
        if (IdentiteSexe(current->Identite)=='M'){
        fprintf(f, "\t%d [label=\"%s\\n%s\\n%s\"];\n",
                IdentiteIdentifiant(current->Identite),
                IdentiteNom(current->Identite),
                IdentitePrenom(current->Identite),
                IdentiteDateNaissance(current->Identite));
        }
        current = current->pSuivante;
    }

    // Changement de couleur pour les femmes
    fprintf(f, "\n\tnode [color = green];\n");

    // Parcourir l'arbre pour écrire les nœuds pour les femmes
    current = Arbre->pPremiere;
    while (current != NULL) {
        if (IdentiteSexe(current->Identite)=='F') {
            fprintf(f, "\t%d [label=\"%s\\n%s\\n%s\"];\n",
                   IdentiteIdentifiant(current->Identite),
                    IdentiteNom(current->Identite),
                    IdentitePrenom(current->Identite),
                    IdentiteDateNaissance(current->Identite));
        }
        current = current->pSuivante;
    }

    // Écriture du style des arcs du graphe
    fprintf(f, "\n\tedge [dir = none];\n");

    // Parcourir l'arbre pour écrire les arcs
    current = Arbre->pPremiere;
    while (current != NULL) {
        if (current->pPere != NULL) {
            fprintf(f, "\t%d -> %d;\n",
                    IdentiteIdentifiant(current->Identite),
                    IdentiteIdentifiant(current->pPere->Identite));
        }
        if (current->pMere != NULL) {
            fprintf(f, "\t%d -> %d;\n",
                    IdentiteIdentifiant(current->Identite),
                    IdentiteIdentifiant(current->pMere->Identite));
        }
        current = current->pSuivante;
    }

    // Écriture de la fermeture du graphe
    fprintf(f, "}\n");

    // Fermeture du fichier
    fclose(f);

    printf("Le fichier DOT a ete genere avec succes : %s\n", Fichier);
}


//fonction auxiliere a ArbreAfficherAscendants
static void AfficherAscendantsRecursive(tArbre Arbre, struct sFiche *personne, int niveau) {
    // Afficher l'identité de la personne
    IdentiteAfficher(personne->Identite);

    // Afficher les ascendants
    if (personne->pPere != NULL) {
        // Afficher le nombre correct de tabulations
        for (int i = 0; i < niveau + 1; i++) {
            printf("\t");
        }
        printf("Pere : ");
        //appeler la fonction récursive
        AfficherAscendantsRecursive(Arbre, personne->pPere, niveau + 1);
    }

    if (personne->pMere != NULL) {
        // Afficher le nombre correct de tabulations
        for (int i = 0; i < niveau + 1; i++) {
            printf("\t");
        }
        printf("Mere : ");
        //appeler la fonction récursive
        AfficherAscendantsRecursive(Arbre, personne->pMere, niveau + 1);
    }
}

void ArbreAfficherAscendants(tArbre Arbre, int Identifiant) {
    struct sFiche *personne = NULL;
    struct sFiche *current = Arbre->pPremiere;

    // Trouver la personne dans l'arbre
    while (current != NULL) {
        if (IdentiteIdentifiant(current->Identite) == Identifiant) {
            personne = current;
            break;
        }
        current = current->pSuivante;
    }

    // Vérifier si la personne a été trouvée
    if (personne == NULL) {
        fprintf(stderr, "Erreur : Identifiant %d non trouvé dans l'arbre.\n", Identifiant);
        return;
    }

    // Appeler la fonction récursive avec le niveau initial 0
    AfficherAscendantsRecursive(Arbre, personne, 0);
}
//fonction auxiliaire 
static void EcrireAscendantsGVRecursive(FILE *f, tArbre Arbre, struct sFiche *personne) {

    if (IdentiteSexe(personne->Identite)=='M'){
        fprintf(f, "\n\tnode [color = red];\n");
    } else {
        fprintf(f, "\n\tnode [color = green];\n");
    } // Change la couleur d'affichage selon le sexe

    fprintf(f, "\t%d [label=\"%s\\n%s\\n%s\", shape=box];\n",
            IdentiteIdentifiant(personne->Identite),
            IdentiteNom(personne->Identite),
            IdentitePrenom(personne->Identite),
            IdentiteDateNaissance(personne->Identite));

    // Écrire les arcs vers les ascendants
    if (personne->pPere != NULL) {
        fprintf(f, "\t%d -> %d;\n",
                IdentiteIdentifiant(personne->Identite),
                IdentiteIdentifiant(personne->pPere->Identite));
        EcrireAscendantsGVRecursive(f, Arbre, personne->pPere);
    }

    if (personne->pMere != NULL) {
        fprintf(f, "\t%d -> %d;\n",
                IdentiteIdentifiant(personne->Identite),
                IdentiteIdentifiant(personne->pMere->Identite));
        EcrireAscendantsGVRecursive(f, Arbre, personne->pMere);
    }
}

void ArbreEcrireAscendantsGV(tArbre Arbre, int Identifiant, char Fichier[]) {
    FILE *f = fopen(Fichier, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s.\n", Fichier);
        return;
    }

    // Écrire l'en-tête du fichier DOT
    fprintf(f, "digraph {\n");
    fprintf(f, "\trankdir = \"BT\";\n");
    // Écriture du style d'écriture
    fprintf(f, "\n\tnode [shape = box, fontname = \"Arial\", fontsize = 10];\n");
    // Écriture du style des arcs du graphe
    fprintf(f, "\n\tedge [dir = none];\n");

    // Trouver la personne dans l'arbre
    struct sFiche *personne = NULL;
    struct sFiche *current = Arbre->pPremiere;

    while (current != NULL) {
        if (IdentiteIdentifiant(current->Identite) == Identifiant) {
            personne = current;
            break;
        }
        current = current->pSuivante;
    }

    // Vérifier si la personne a été trouvée
    if (personne == NULL) {
        fprintf(stderr, "Erreur : Identifiant %d non trouvé dans l'arbre.\n", Identifiant);
        fclose(f);
        return;
    }

    // Appeler la fonction récursive pour écrire les ascendants
    EcrireAscendantsGVRecursive(f, Arbre, personne);

    // Écrire la fermeture du fichier DOT
    fprintf(f, "}\n");

    fclose(f);
}
