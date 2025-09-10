#include <stdio.h>


int tupleSameProduct(int* nums, int numsSize) {
    int lens = (numsSize * (numsSize - 1)) / 2;
    int tab[lens];
    int compteur = 0;
    int index = 0;
    for(int i = 0;i<numsSize;i++){
        for(int j = i+1; j<numsSize;j++){
            tab[index++]=nums[i]*nums[j];
       
            for(int x = 0;x<lens;x++){
                for(int y = x;y<lens;y++){
                    if(tab[x]==tab[y]){
                        compteur++;
            }
        }
    }
 }
    }
    return compteur;
    


}
