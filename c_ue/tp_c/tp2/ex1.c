#include <stdlib.h>

int main(void){
    int x;
    printf("Choisie une année\n ");
    scanf("%d",x);
    if(x%4==0 && x%100!=0){
        printf("pas bissextille");
    }
    else{
        printf("bissextille");
    }
        return 0;
}


