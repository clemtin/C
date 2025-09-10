#include "date.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct sDate dated;


int main(){
    dated debut = {2000,1,1,00,00};
    dated fin = {2023,12,31,23,59};
    dated date1 = {2003,10,19,22,28};
    dated date2 = {2003,07,28,9,32};

    char dateArrange[14];

    YYYYMMDDTHHMM(dateArrange,date1);

    printf("%d, %d, %d, %d\n", EstValide(date1), Compare(date1,date2),
    Appartient(date1,debut,fin),Chevauche(debut,fin,date1,date2));

    printf("%s\n",dateArrange);
    return 0;
}