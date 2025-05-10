#include "date.h"
#include <stdio.h>
#include <stdlib.h>
typedef const struct sDate dated;

/* si c'est valide 1 sinon 0 */
int EstValide(dated date) {
    if (date.annee >= 0000 && date.annee <= 2100 &&    
        date.mois >= 1 && date.mois <= 12 &&           
        date.jour >= 1 && date.jour <= 31 &&           
        date.heure <= 23 &&                            
        date.minute <= 59) {                           
        return 1; 
    }
    return 0; 
}


 /* COMAPRE(DATE1,DATE2) => DATE1>DATE2 => 1 SINON -1  */
int Compare(dated reference, dated autredate){
    if(reference.annee == autredate.annee &&
    reference.mois == autredate.mois &&
    reference.jour == autredate.jour &&
    reference.heure == autredate.heure &&
    reference.minute == autredate.minute){
        return 0;
    }
   
    if((reference.annee > autredate.annee) 
    || (reference.annee == autredate.annee) && (reference.mois > autredate.mois)
    || (reference.annee == autredate.annee) && (reference.mois == autredate.mois) && 
    (reference.jour > autredate.jour) 
    || (reference.annee == autredate.annee) && (reference.mois == autredate.mois) &&
    (reference.jour == autredate.jour) && (reference.heure > autredate.heure) 
    ||(reference.annee == autredate.annee) && (reference.mois == autredate.mois) &&
    (reference.jour == autredate.jour) && (reference.heure == autredate.heure) &&
    (reference.minute > autredate.minute)){
        return 1;}
    else{
        return -1;
    }
}

int Appartient(dated date, dated debut, dated fin){
   /*          rappel des sorties de COMPARE
    COMAPRE(DATE1,DATE2) => DATE1>DATE2 => 1 SINON -1 
     */

    if(((Compare(debut,date)==0) || (Compare(fin,date)==0))
    || ((Compare(fin,date)==1) && (Compare(debut,date)==-1)))
    {
        return 1;
    }
    return 0;   
}





int Chevauche(dated debut1, dated fin1, dated debut2, dated fin2){
    /*          rappel des sorties de COMPARE
    COMAPRE(DATE1,DATE2) => DATE1>DATE2 => 1 SINON -1 
     */

    if((Compare(debut2,debut1)>=0 && Compare(fin2,debut2)>=0
    || Compare(fin2,debut1)>=0) && Compare(fin1,fin2)>=0){
        return 1;
    }

    return 0;

}


void YYYYMMDDTHHMM(char* destination, dated date){
    sprintf(destination, "%04u%02u%02uT%02u%02u\0",date.annee,date.mois,date.jour,date.heure,date.minute);
}
