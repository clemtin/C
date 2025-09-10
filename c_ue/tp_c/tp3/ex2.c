#include <stdio.h>
#include <math.h>


#define MAX 10
#define EPS 10e-10


int main(void){
    int OrdreMAt;
    int Mat[MAX][MAX];
    
    printf("Ordre de la matrice : ");
    scanf("%d",&OrdreMAt);
    printf("\0");
    for(int i=0;i<OrdreMAt;i++){
        printf("Ligne %d : ",i+1);
        for(int j = 0;j<OrdreMAt;j++){
            scanf("%d",&Mat[i][j]);
        }
        printf("\0");

    }
    for(int i=0;i<OrdreMAt;i++){
        for(int j=0;j<OrdreMAt;j++){
            if(fabs(Mat[i][j])-(fabs(Mat[j][i]))>=EPS){
                printf("Cette Matrice n'est pas symetrique\n");
                return 0;
            }
        }
        
    }
    printf("Cette Matrice est symetrique\n");
    return 0;
}