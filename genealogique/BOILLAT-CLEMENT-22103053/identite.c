#include "identite.h"


#define LG_DATE 10 // Nbr cara d'une date de format jj/mm/aaaa
#define LG_LIGNE 80 // nbr ligne 


// Identité d’une personne
struct sIdentite
    {
    int Identifiant ; // Identifiant unique
    char * Nom ; // Nom (chaîne de caract ères allou ée dynamiquement )
    char * Prenom ; // Prénom (cha îne de caract ères allou ée dynamiquement )
    char Sexe ; // ’F’ ou ’M’
    char DateNaissance [ LG_DATE +1]; // Date de naissance sous la forme jj/mm/ aaaa
    };




tIdentite IdentiteCreer(int Id, char *Nom, char *Prenom, char Sexe, char DateNais[]){
    tIdentite identite = malloc(sizeof(struct sIdentite));
    if(identite == NULL){
        return NULL;
    }

    identite->Identifiant=Id;
    identite->Nom = malloc(strlen(Nom) + 1); // +1 pour le caractère de fin '\0'
    if (identite->Nom == NULL) {
        free(identite);
        return NULL;
    }
    sprintf((identite->Nom),"%s",Nom);

    identite->Prenom = malloc(strlen(Prenom) + 1);
    if (identite->Prenom == NULL) {
        free(identite->Nom);
        free(identite);
        return NULL;
    }
    sprintf((identite->Prenom),"%s",Prenom);

    (identite->Sexe)=Sexe;

    sprintf((identite->DateNaissance), "%s",DateNais);
    
    return identite;
}


int IdentiteIdentifiant(tIdentite Identite){
    return(Identite->Identifiant);
    //: retourne l’identifiant de la personne décrite par Identite//

}

char *IdentiteNom(tIdentite Identite){
    return(Identite->Nom);
    // : retourne l’adresse du premier caractère du nom de la  personne décrite par Identite    

}

char *IdentitePrenom(tIdentite Identite){
    return(Identite->Prenom);
    /*
    : retourne l’adresse du premier caractère du prénom
    de la personne décrite par Identite.
    • 
    */

} 
char IdentiteSexe(tIdentite Identite){
    return(Identite->Sexe);
    /*
    : retourne le sexe (’F’ ou ’M’) de la personne décrite
    par Identite.
    */

} 

char *IdentiteDateNaissance(tIdentite Identite){
    return((Identite->DateNaissance));
    /* 
     : retourne l’adresse du premier caractère de
    la date de naissance de la personne décrite par Identite.
    */

}


void IdentiteAfficher(tIdentite Identite) {
    printf("[%d] %s %s, %c, %s\n", Identite->Identifiant, 
        Identite->Nom, Identite->Prenom, Identite->Sexe, Identite->DateNaissance);
    /* 
    : affiche à l’écran les informations données par
Identite sous la forme d’une ligne ayant le modèle suivant (␣ représente un caractère espace) :
[identifiant]␣nom␣prénom,␣sexe,␣date de naissance
Avec l’exemple donné ci-dessus, cette fonction doit afficher la ligne :
[16]␣DUFF␣John,␣M,␣13/12/2001
*/
}

void IdentiteLiberer(tIdentite Identite) {
    if(Identite !=NULL){
        free(Identite->Nom);
        free(Identite->Prenom);
        free(Identite);
    
    }
   
}

static int nettoyer(char *ligne) {
    // Supprime le '\n' final s'il existe
    int i = 0;
    while (ligne[i] != '\0') {
        if (ligne[i] == '\n') {
            ligne[i] = '\0';
            return 0;
        }
        i++;
    }
    return 1;
}


tIdentite IdentiteLiref(FILE *f) {    
    char nom[LG_LIGNE+1];
    char prenom[LG_LIGNE+1];
    char sexe[LG_LIGNE+1];
    char date[LG_DATE + 1];
    int identifiant;
    char * pNom = nom;
    char * pPrenom = prenom;
    char * pDate = date;

    if (f == NULL) return NULL;


    if (fscanf(f, "%d", &identifiant) != 1) return NULL;
    fgetc(f); // pour consommer le '\n'

    // nom
        if (fgets(nom, LG_LIGNE, f) == NULL) return NULL;
        nettoyer(nom);
        
    // prenom
        if (fgets(prenom, LG_LIGNE, f) == NULL) return NULL;
        nettoyer(prenom);
        
    // sexe
        if (fgets(sexe, LG_LIGNE, f) == NULL) return NULL;
        char sexe_char = sexe[0];
        
    // date
        if (fgets(date, LG_DATE + 1, f) == NULL) return NULL;
        nettoyer(date);
        
    // Affichage (test)
    tIdentite id = IdentiteCreer(identifiant, pNom, pPrenom, sexe_char, pDate);

return id;
}   
