#include <stdio.h>


int main(void){
    int max = 0;
    printf("max de table \n");
    scanf("%d",&max);
    while(max>18 || max<0){
        scanf("%d",&max);
    }
    printf("x |");
    for(int i = 0;i<=max;i++){
        printf("%3d",i);

    }
    printf("\n");
    printf("---");
    for(int i = 0; i <= max; i++) {
        printf("---");
}
printf("\n");
for (int i = 0; i <= max; i++) {
        printf("%2d |", i);
        for (int j = 0; j <= max; j++) {
            printf("%3d", i * j);
        }
        printf("\n");
    }


    return 0;
}